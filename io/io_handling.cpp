#include "io_handling.hpp"
#include "../engine/interface.hpp"
#include "../game/textures.hpp"
#include <cstdint>
#include <variant>
#include <cctype>
#include "../datastructures/vector3.hpp"
#include "../datastructures/orientation.hpp"
#include "input.hpp"
#include "../game/player.hpp"

void io::IoHandler::writeOutput(engine::EntityInterface& entity) {
	renderer.startFrame();
	for (double pitchOffset = orientationLimit.pitch; pitchOffset >= -orientationLimit.pitch; pitchOffset -= orientationDelta.pitch) {
		for (double yawOffset = -orientationLimit.yaw; yawOffset <= orientationLimit.yaw; yawOffset += orientationDelta.yaw) {
			const engine::BlockOffset block = entity.findBlock({yawOffset, pitchOffset});
			renderer.write(game::resolveColour(static_cast<game::Block>(block.block), block.offset));
		}
		renderer.writeLine();
	}
	renderer.flush();
}

void io::IoHandler::readInput(engine::EntityInterface& entity, bool& quit) {
	input.read(inputBuffer);
	quit = false;
	for (auto& data : inputBuffer) {
		if (data.index() == 0) {
			auto [key, down] = std::get<0>(data);
			game::Direction start = player.getMovementDirection();
			switch (static_cast<char>(std::tolower(static_cast<unsigned char>(key)))) {
				case 'w':
					player.move(game::UP, down);
					break;
				case 's':
					player.move(game::DOWN, down);
					break;
				case 'd':
					player.move(game::RIGHT, down);
					break;
				case 'a':
					player.move(game::LEFT, down);
					break;
				case ' ':
					entity.jump();
					break;
				default:
					if (key >= '0' && key <= '9') {
						const uint32_t slot = key - '0';
						player.selectItem(slot);
					}
			}
			game::Direction direction = player.getMovementDirection();
			if (start != direction) {
				entity.setMovementDirection({(double)direction.right - (double)direction.left, (double)direction.up - (double)direction.down});
			}
		}
		else if (data.index() == 1) {
			MouseButtons mouseButtons = std::get<1>(data);
			if (mouseButtons.right) {
				entity.placeBlock(player.getSelectedItem());
			}
		}
		else if (data.index() == 2) {
			Point point = std::get<2>(data);
			Orientation rotation(((int32_t)point.x - (int32_t)mousePointer.x) * sensitivity, ((int32_t)point.y - (int32_t)mousePointer.y) * sensitivity);
			mousePointer = point;
			entity.rotate(rotation);
		}
		else if (data.index() == 3) {
			SpecialKey specialKey = std::get<3>(data);
			if (specialKey == ESCAPE) {
				quit = true;

			}
		}
	}
	inputBuffer.clear();
}

