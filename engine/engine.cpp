#include "engine.hpp"
#include <thread>
#include "../datastructures/vector3.hpp"
#include <optional>
#include "interface.hpp"
#include <chrono>
#include <algorithm>

void engine::GameEngine::update() {
    for (auto& [state, hitbox, _] : entities) {
        Vector3 force{};
        state.velocity.z -= physics.gravity;
        const Vector2 points[4] = {{hitbox.x, hitbox.y}, {-hitbox.x, -hitbox.y}, {-hitbox.x, hitbox.y}, {hitbox.x, -hitbox.y}};
        for (const Vector2& point : points) {
            Vector3 pos = state.position + point;
			pos.z -= hitbox.z;
            if (!world.get(pos).has_value()) continue;
			force.z = -state.velocity.z;
        }
        for (double i = 0; i <= hitbox.z + 1 ; i += 0.5) {
            const double hitboxPos = std::min(i, hitbox.z);
            for (Vector3 offset : points) {
                offset.z = hitboxPos;
                if (!world.get(state.position + offset).has_value()) continue;
                if (const Vector3 difference = offset.abs(); difference.y <= hitbox.y) {
                    force.y = -state.velocity.y;
                } else if (difference.x <= hitbox.x) {
                    force.x = -state.velocity.x;
                }
                break;
            }
        }
        state.velocity += force;
        state.update(physics.friction);
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