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
        const Vector2 points[4] = {{e.hitbox.x, e.hitbox.y}, {-e.hitbox.x, -e.hitbox.y}, {-e.hitbox.x, e.hitbox.y}, {e.hitbox.x, -e.hitbox.y}};
        for (const Vector2& point : points) {
            Vector3 pos = e.position + point;
			pos.z -= e.hitbox.z;
            if (!world.get(pos).has_value()) continue;
			force.z = -e.velocity.z;
        }
        for (double i = 0; i <= e.hitbox.z + 1 ; i += 0.5) {
            const double hitboxPos = std::min(i, e.hitbox.z);
            for (Vector3 offset : points) {
                offset.z = hitboxPos;
                if (!world.get(e.position + offset).has_value()) continue;
                const Vector3 difference = offset.abs();
                if (difference.y <= e.hitbox.y) {
                    force.y = -e.velocity.y;
                } else if (difference.x <= e.hitbox.x) {
                    force.x = -e.velocity.x;
                }
                break;
            }
        }
        e.velocity += force;
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