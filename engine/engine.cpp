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

static double closestBock(const Vector3& position, const double originalAxisPosition, const Vector3& volume, const Vector3::Axis axis, const engine::LimitedBlockWorld& world, const double velocity) {
    double minDistance = std::abs(velocity);
    const Vector3 end = (position + volume).ceil();
    for (double z = position.z; z < end.z; z += 1) {
        for (double y = position.y; y < end.y; y += 1) {
            for (double x = position.x; x < end.x; x += 1) {
                const Vector3 blockPosition = {x, y, z};
                if (!world.get(blockPosition).has_value()) {
                    continue;
                }
                if (const double distance = std::abs(blockPosition.get(axis) - originalAxisPosition); distance < minDistance) {
                    minDistance = distance;
                }
            }
        }
    }
    return minDistance;
}

static Vector3 limitMovement(const Vector3& position, const Vector3& hitbox, const Vector3& velocity, const engine::LimitedBlockWorld& world) {
    const Vector3 sign = Vector3(velocity.sign());
    const Vector3 originalPosition = position + hitbox * sign;
    const Vector3 start = originalPosition + Vector3(
        velocity.x < 0 ? velocity.x : 0, 
        velocity.y < 0 ? velocity.y : 0, 
        velocity.z < 0 ? velocity.z : 0);
    const Vector3 volume = hitbox * 2;
	const Vector3 absVelocity = velocity.abs();
    const double xBlock = velocity.x == 0 ? 0 : closestBock(start, originalPosition.x, volume.withX(absVelocity.x), Vector3::X, world, velocity.x);
    const double yBlock = velocity.y == 0 ? 0 : closestBock(start, originalPosition.y, volume.withY(absVelocity.y), Vector3::Y, world, velocity.y);
    const double zBlock = velocity.z == 0 ? 0 : closestBock(start, originalPosition.z, volume.withZ(absVelocity.z), Vector3::Z, world, velocity.z);
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