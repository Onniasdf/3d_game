#ifndef INC_3D_GAME_ENGINE_HPP
#define INC_3D_GAME_ENGINE_HPP

#include <chrono>
#include <functional>
#include <vector>
#include <bits/this_thread_sleep.h>

#include "entity.hpp"
#include "interface.hpp"
#include "world.hpp"

namespace engine {

    template <engine::Interactable TWorld>
    class GameEngine {
        TWorld world;
        std::vector<Entity> entities;
        std::vector<std::function<void(WorldInterface<TWorld>&)>> callbacks;
        std::chrono::milliseconds updateDelay;
        Physics physics;
        RgbColour* colourMap;
        bool running = true;
        uint64_t tick = 0;

        void update();
    public:
        GameEngine(TWorld world, const std::chrono::milliseconds updateDelay, const Physics& physics, RgbColour* colourMap) : world(world), updateDelay(updateDelay), physics(physics), colourMap(colourMap) {}

        void onTick(const std::function<void(WorldInterface<TWorld>&)>& callback) {
            callbacks.push_back(callback);
        }

        void run();
    };
}

#endif
