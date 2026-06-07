#include "player.hpp"
#include <cstdarg>
#include <cstdint>



void game::Player::selectItem(const uintptr_t index) {
	selectedItem = static_cast<uint16_t>(index);
}

uint16_t game::Player::getSelectedItem() const {
	return selectedItem;
}

void game::Player::move(const DirectionType direction, const bool set) {
	switch (direction) {
		case UP:
			movementDirection.up = set;
			break;
		case DOWN:
			movementDirection.down = set;
			break;
		case LEFT:
			movementDirection.left = set;
			break;
		case RIGHT:
			movementDirection.right = set;
			break;
	}
}