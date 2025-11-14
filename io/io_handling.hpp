#ifndef GAME_HPP
#define GAME_HPP

#include "input.hpp"
#include "rendering.hpp"
#include "../datastructures/orientation.hpp"
#include "../engine/interface.hpp"
#include "../engine/world.hpp"
#include "../datastructures/vector3.hpp"

namespace io {
    struct Direction {
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;

        bool operator==(const Direction& other) const {
            return up == other.up && down == other.down && left == other.left && right == other.right;
        }
    };

    class IoHandler {
        Renderer renderer{};
        Orientation orientationLimit;
        Orientation orientationDelta;
        InputListener input;
        std::vector<std::variant<KeyboardEvent, MouseButtons, Point>> inputBuffer;
        Direction direction{};
        uint32_t currentBlock = 0;

        
    public:
        IoHandler(const Orientation fieldOfView, const Point screenSize, InputListener input) :
        orientationLimit({fieldOfView.yaw / 2, fieldOfView.pitch / 2}),
        orientationDelta({fieldOfView.yaw / screenSize.x, fieldOfView.pitch / screenSize.y}),
        input(input) {}

        template <engine::Interactable TWorld>
        void writeOutput(engine::EntityInterface<TWorld>& player);

        template <engine::Interactable TWorld>
        void readInput(engine::EntityInterface<TWorld>& player);
    };
}

#endif
