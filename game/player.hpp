#pragma once
#include <cstdarg>
#include <cstdint>

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
    };


	class Player {
        uint16_t selectedItem = 0;
		Direction movementDirection{};
	public:
		Player() = default;

		void selectItem(uintptr_t index);
		uint16_t getSelectedItem() const;
		void move(DirectionType direction, bool set);
        Direction getMovementDirection() const {
            return movementDirection;
		}
	};
}