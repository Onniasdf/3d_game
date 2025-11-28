#include "engine.hpp"
#include <thread>
#include <cstdint>
#include "../datastructures/vector3.hpp"
#include <optional>
#include "interface.hpp"
#include <chrono>
#include <algorithm>

void engine::GameEngine::update() {
    for (auto& e : entities) {
        Vector3 force{};
        e.velocity.z -= physics.gravity;
        const Vector3 points[4] = {{e.hitbox.x, e.hitbox.y, 0}, {-e.hitbox.x, -e.hitbox.y, 0}, {-e.hitbox.x, e.hitbox.y, 0}, {e.hitbox.x, -e.hitbox.y, 0}};
        for (double i = -e.hitbox.z; i <= e.hitbox.z + 1 ; i++) {
            const double hitboxPos = std::min(i, e.hitbox.z);
            for (const auto& offset : points) {
                Vector3 point = e.position + offset;
                point.z += hitboxPos;
                if (!world.get(point).has_value()) continue;
                const Vector3 difference = offset.withZ(hitboxPos).abs();
                if (difference.z <= e.hitbox.z) {
                    force.z = -e.velocity.z;
                } else if (difference.y <= e.hitbox.y) {
                    force.y = -e.velocity.y;
                } else if (difference.x <= e.hitbox.x) {
                    force.x = -e.velocity.x;
                }
                break;
            }
        }
        e.velocity += force;
        e.velocity = e.velocity.clamp(-1,1);
        e.update(physics.friction);
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