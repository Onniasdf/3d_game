#include "engine.hpp"
#include <cmath>

template <engine::Interactable TWorld>
void engine::GameEngine<TWorld>::update() {
    for (auto& e : entities) {
        Vector3 force{};
        const Vector3 points[4] = {{e.hitbox.x, e.hitbox.y, 0}, {-e.hitbox.x, -e.hitbox.y, 0}, {-e.hitbox.x, e.hitbox.y, 0}, {e.hitbox.x, -e.hitbox.y, 0}};
        for (int32_t i = -e.hitbox.z; i <= e.hitbox.z + 1 ; i++) {
            const double hitboxPos = std::max(static_cast<double>(i), e.hitbox.z);
            for (const auto & offset : points) {
                Vector3 point = e.position + offset;
                point.z += hitboxPos;
                if (std::optional<uint64_t> block = world.get(point); !block.has_value()) continue;
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
        force.z -= physics.gravity;
        e.update(force, physics.friction);
    }
}



template <engine::Interactable TWorld>
void engine::GameEngine<TWorld>::run() {
    std::chrono::time_point<std::chrono::steady_clock> tickTime = std::chrono::steady_clock::now();
    while (running) {
        update();
        WorldInterface<TWorld> interface {&world, colourMap, &running, &entities, &physics};
        for (auto& c : callbacks) {
            c(interface);
        }
        tick++;
        tickTime += updateDelay;
        std::this_thread::sleep_until(tickTime);
    }
}