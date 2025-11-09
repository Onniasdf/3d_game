#ifndef GAME_HPP
#define GAME_HPP

#include "rendering.hpp"
#include "../datastructures/orientation.hpp"
#include "../engine/interface.hpp"
#include "../engine/world.hpp"

namespace game {
    class GameHandler {
        Renderer renderer;
        Orientation fieldOfView;
        Orientation orientationLimit;
        Orientation orientationDelta;
        
    public:
        template <engine::Interactable TWorld>
        void render(engine::EntityInterface<TWorld>& player);

        template <engine::Interactable TWorld>
        void readInput(engine::EntityInterface<TWorld>& player);
    };
}

#endif
