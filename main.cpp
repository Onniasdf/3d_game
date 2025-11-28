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
#include "io/texture.hpp"
#include <utility>


int main() {
    io::Texture colours[10] = {
        {{0, 0, 1}},       // black
        {{255, 0, 0}},     // red
        {{0, 255, 0}},     // green
        {{0, 0, 255}},     // blue
        {{255, 255, 0}},   // yellow
        {{255, 0, 255}},   // magenta
        {{0, 255, 255}},   // cyan
        {{128, 128, 128}}, // gray
        {{255, 128, 0}},   // orange
        {{128, 0, 128}}    // purple
    };
    engine::LimitedBlockWorld world{50,50,50};
    for (int i = -50; i < 50; i++) {
        for (int j = -50; j < 50; j++) {
            world.set({ (double)i, (double)j, 0 }, 2);
        }
    }
    engine::Physics physics = engine::Physics::calculateFromPerSecond(20, 3, 2, 1.3);
    engine::GameEngine game{std::move(world), std::chrono::milliseconds(1000) / 20, physics};
    io::InputListener listener = io::InputListener::create();
    io::IoHandler ioHandler{{std::numbers::pi / 2, std::numbers::pi}, {100, 30}, 0.001, listener, colours};
    size_t entityIndex = 0;
    game.onTick([&](engine::WorldInterface& interface) {
        std::optional<engine::EntityInterface> entity = interface.getEntity(entityIndex);
        if (!entity.has_value()) {
            entityIndex = interface.addEntity({0, 0, 2}, {1. / 3, 1. / 3, 1});
            return;
        }
        ioHandler.readInput(entity.value());
        ioHandler.writeOutput(entity.value());
    });
    game.run();
}
