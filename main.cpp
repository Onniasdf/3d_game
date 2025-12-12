#include "engine/engine.hpp"
#include "engine/block_world.hpp"
#include "io/io_handling.hpp"
#include "engine/interface.hpp"
#include <chrono>
#include <optional>
#include <numbers>
#include "io/input.hpp"
#include "engine/physics.hpp"
#include "datastructures/rgb_colour.hpp"
#include "game/textures.hpp"
#include <utility>


int main() {
    engine::LimitedBlockWorld world{50,50,50};
    for (int i = -50; i < 50; i++) {
        for (int j = -50; j < 50; j++) {
            world.set({ (double)i, (double)j, 0 }, game::GRASS);
        }
    }
    const int ticks = 20;
    engine::Physics physics = engine::Physics::calculateFromPerSecond(ticks, 3, 3, 20);
    engine::GameEngine game{std::move(world), std::chrono::milliseconds(1000) / ticks, physics};
    io::InputListener listener = io::InputListener::create();
    io::IoHandler ioHandler{{std::numbers::pi / 2, std::numbers::pi / 2}, {300, 50}, 0.1, listener};
    size_t entityIndex = 0;
    game.onTick([&](engine::WorldInterface& interface) {
        std::optional<engine::EntityInterface> entity = interface.getEntity(entityIndex);
        if (!entity.has_value()) {
            entityIndex = interface.addEntity({0, 0, 2}, {1. / 3, 1. / 3, 1});
            return;
        }
        bool quit;
        ioHandler.readInput(entity.value(), quit);
        if (quit) {
            interface.end();
			return;
        }
        ioHandler.writeOutput(entity.value());
    });
    game.run();
}
