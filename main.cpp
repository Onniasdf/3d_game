#include "engine/engine.hpp"
#include "engine/block_world.hpp"
#include "io/io_handling.hpp"
#include "engine/interface.hpp"
#include <chrono>
#include <optional>
#include <numbers>
#include "io/input.hpp"
#include "engine/physics.hpp"
#include "game/textures.hpp"
#include <utility>


int main() {
    engine::LimitedBlockWorld world{50,50,50};
    for (int i = -50; i < 50; i++) {
        for (int j = -50; j < 50; j++) {
            world.set({ static_cast<double>(i), static_cast<double>(j), 0 }, game::GRASS);
        }
    }
    constexpr int ticks = 20;
    const engine::Environment physics = engine::Environment::calculateFromPerSecond(ticks, 3, 3, 1.5);
    engine::GameEngine game{std::move(world), std::chrono::milliseconds(1000) / ticks, physics};
    const io::InputListener listener = io::InputListener::create();
    io::IoHandler ioHandler{{std::numbers::pi / 2, std::numbers::pi / 2}, {300, 70}, 0.1, listener};
    size_t entityIndex = 0;
    game.onTick([&](const engine::WorldInterface& interface) {
        std::optional<engine::EntityInterface> entity = interface.getEntity(entityIndex);
        if (!entity.has_value()) {
            entityIndex = interface.addEntity({0, 0, 0}, {1, 1, 2});
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
