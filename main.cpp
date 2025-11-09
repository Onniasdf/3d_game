#include "engine/engine.hpp"
#include "engine/block_world.hpp"
#include <memory>
#include <chrono>
#include <sstream>
#include "game/rendering.hpp"
#include <optional>

int main() {
    uint32_t screenWitdh = 40, screenHeight = 20;
    double yaw = 90, pitch = 180;
    double yawDelta = yaw / screenWitdh, pitchDelta = pitch / screenHeight;
    double yawLimit = yaw / 2, pitchLimit = pitch / 2;
    size_t entityIndex = 0;
    engine::LimitedBlockWorld world{50,50,50};
    engine::Physics physics = engine::Physics::calculateFromMetersPerSecond(20, 32, 4);
    engine::GameEngine<engine::LimitedBlockWorld> engine{world, std::chrono::milliseconds(1000) / 20, physics, nullptr};
    game::Renderer renderer{};
    engine.onTick([&](engine::WorldInterface<engine::LimitedBlockWorld>& interface) {
        renderer.startFrame();
        std::optional<engine::EntityInterface<engine::LimitedBlockWorld>> entity = interface.getEntity(entityIndex);
        if (!entity.has_value()) {
            entityIndex = interface.addEntity({}, {1 / 3, 1 / 3, 1});
        }
        for (double pitchOffset = -pitchLimit; pitchOffset < pitchLimit; pitchOffset += pitchDelta) {
            for (double yawOffset = -yawLimit; yawOffset < yawLimit; yawOffset += yawDelta) {
            }
        }
    });
    engine.run();
}