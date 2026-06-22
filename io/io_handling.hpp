#pragma once

#include "input.hpp"
#include "rendering.hpp"
#include "../datastructures/orientation.hpp"
#include "../engine/interface.hpp"
#include "../datastructures/vector3.hpp"
#include "../game/player.hpp"
#include <vector>
#include <variant>

namespace io {
    class IoHandler {
        Renderer renderer{};
        Orientation orientationLimit;
        Orientation orientationDelta;
        InputListener input;
        std::vector<std::variant<KeyboardEvent, MouseButtons, Point2, SpecialKey>> inputBuffer;
        Point2 mousePointer{};
        double sensitivity;
        
        game::Player player{};

        
    public:
        IoHandler(const Orientation fieldOfView, const Point2 screenSize, const double mouseSensitivity, const InputListener& input) :
        orientationLimit({fieldOfView.yaw / 2, fieldOfView.pitch / 2}),
        orientationDelta({fieldOfView.yaw / screenSize.x, fieldOfView.pitch / screenSize.y}),
        input(input),
        sensitivity(mouseSensitivity) {}

        void writeOutput(const engine::EntityInterface& player);

        void readInput(engine::EntityInterface& player, bool& quit);
    };
}