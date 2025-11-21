#ifndef INC_3D_GAME_ENGINE_HPP
#define INC_3D_GAME_ENGINE_HPP

#include <chrono>
#include <functional>
#include <vector>
#include "physics.hpp"
#include "interface.hpp"
#include <cstdint>
#include "../datastructures/rgb_colour.hpp"
#include "block_world.hpp"
#include <utility>

namespace engine {


    class GameEngine {
        LimitedBlockWorld world;
        std::vector<Entity> entities;
        std::vector<std::function<void(WorldInterface&)>> callbacks;
        std::chrono::milliseconds updateDelay;
        Physics physics;
        bool running = true;
        uint64_t tick = 0;

        void update();
    public:
        GameEngine(LimitedBlockWorld world, const std::chrono::milliseconds updateDelay, const Physics& physics) : world(std::move(world)), updateDelay(updateDelay), physics(physics) {}

        void onTick(const std::function<void(WorldInterface&)>& callback) {
            callbacks.push_back(callback);
        }

        void run();
    };

}

#endif
