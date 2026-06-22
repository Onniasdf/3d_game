#pragma once
#include <cstdarg>
#include <cstdint>
#include "../datastructures/vector2.hpp"

namespace game {
    enum DirectionType {
        UP,
        DOWN,
        LEFT,
        RIGHT
	};

    struct Direction {
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;

        bool operator==(const Direction& other) const {
            return up == other.up && down == other.down && left == other.left && right == other.right;
        }

        [[nodiscard]] Vector2 getVector() const {
            return {static_cast<double>(right) - static_cast<double>(left), static_cast<double>(up) - static_cast<double>(down)};
        }
    };


	class Player {
        uint16_t selectedItem = 0;
		Direction movementDirection{};
	public:
		Player() = default;

		void selectItem(uintptr_t index);
		[[nodiscard]] uint16_t getSelectedItem() const;
		void move(DirectionType direction, bool set);
        [[nodiscard]] Direction getMovementDirection() const {
            return movementDirection;
		}
	};
}