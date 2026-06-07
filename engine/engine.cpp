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

double closestBock(const Vector3& position, const Vector3& volume, const Vector3::Axis axis, const engine::LimitedBlockWorld& world, const double velocity) {
    double minDistance = velocity;
    const Vector3 end = (position + volume).ceil();
    for (double z = position.z; z < end.z; z += 1.0) {
        for (double y = position.y; y < end.y; y += 1.0) {
            for (double x = position.x; x < end.x; x += 1.0) {
                const Vector3 blockPosition = {x, y, z};
                if (!world.get(blockPosition).has_value()) {
                    continue;
                }
                if (const double distance = std::abs(blockPosition.get(axis) - position.get(axis)); distance < minDistance) {
                    minDistance = distance;
                }
            }
        }
    }
    return minDistance;
}

Vector3 limitMovement(const Vector3& position, const Vector3& hitbox, const Vector3& velocity, const engine::LimitedBlockWorld& world) {
    const Vector3 target = position + velocity;
    double xBlock = closestBock(position.withX(target.x), hitbox, Vector3::Axis::X, world, velocity.x);
    double yBlock = closestBock(position.withY(target.y), hitbox, Vector3::Axis::Y, world, velocity.y);
    double zBlock = closestBock(position.withZ(target.z), hitbox, Vector3::Axis::Z, world, velocity.z);
    return {xBlock, yBlock, zBlock};
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