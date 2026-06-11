#include "engine.hpp"
#include <thread>
#include "../datastructures/vector3.hpp"
#include <optional>
#include "interface.hpp"
#include <chrono>
#include <algorithm>
#include <filesystem>


static void updateEntityState(engine::EntityState& state, const double friction) {
    state.position += state.velocity;
    state.velocity += state.acceleration;
    state.acceleration *= 1 - friction;
}

double closestBock(const Vector3& position, const Vector3& originalPosition, const Vector3& volume, const Vector3::Axis axis, const engine::LimitedBlockWorld& world, const double velocity) {
    double minDistance = std::abs(velocity);
    const Vector3 end = (position + volume).ceil();
    for (double z = position.z; z < end.z; z += 1) {
        for (double y = position.y; y < end.y; y += 1) {
            for (double x = position.x; x < end.x; x += 1) {
                const Vector3 blockPosition = {x, y, z};
                if (!world.get(blockPosition).has_value()) {
                    continue;
                }
                if (const double distance = std::abs(blockPosition.get(axis) - originalPosition.get(axis)); distance < minDistance) {
                    minDistance = distance;
                }
            }
        }
    }
    return minDistance;
}

Vector3 limitMovement(const Vector3& position, const Vector3& hitbox, const Vector3& velocity, const engine::LimitedBlockWorld& world) {
    const Vector3 sign = velocity.sign();
    const Vector3 start = position - hitbox;
    const Vector3 target = start + velocity;
    const Vector3 originalPosition = position + hitbox * sign;
    const Vector3 volume = hitbox * 2;
    const double xBlock = velocity.x == 0 ? 0 : closestBock(start.withX(target.x), originalPosition, volume, Vector3::X, world, velocity.x);
    const double yBlock = velocity.y == 0 ? 0 : closestBock(start.withY(target.y), originalPosition, volume, Vector3::Y, world, velocity.y);
    const double zBlock = velocity.z == 0 ? 0 : closestBock(start.withZ(target.z), originalPosition, volume, Vector3::Z, world, velocity.z);
    return Vector3(xBlock, yBlock, zBlock) * sign;
}

static void updateEntity(engine::EntityInformation& entity, const engine::Environment& physics, const engine::LimitedBlockWorld& world) {
    entity.state.velocity = limitMovement(entity.state.position, entity.hitbox, entity.state.velocity, world);
    updateEntityState(entity.state, physics.friction);
}

void engine::GameEngine::update() {
    for (auto& e : entities) {
        updateEntity(e, physics, world);
    }
}

void engine::GameEngine::run() {
    std::chrono::time_point<std::chrono::steady_clock> tickTime = std::chrono::steady_clock::now();
    while (running) {
        update();
        WorldInterface interface {world, running, entities, physics};
        for (auto& c : callbacks) {
            c(interface);
        }
        tick++;
        tickTime += updateDelay;
        std::this_thread::sleep_until(tickTime);
    }
}