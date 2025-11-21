#include "io_handling.hpp"
#include "../datastructures/rgb_colour.hpp"
#include "../engine/interface.hpp"
#include <cstdint>
#include <variant>
#include <cctype>
#include "../datastructures/vector3.hpp"
#include "../datastructures/orientation.hpp"
#include "input.hpp"
#include "../game/player.hpp"

void io::IoHandler::writeOutput(engine::EntityInterface& entity) {
	renderer.startFrame();
	for (double pitchOffset = -orientationLimit.pitch; pitchOffset <= orientationLimit.pitch; pitchOffset += orientationDelta.pitch) {
		for (double yawOffset = -orientationLimit.yaw; yawOffset <= orientationLimit.yaw; yawOffset += orientationDelta.yaw) {
			const uint16_t block = entity.findBlock({yawOffset, pitchOffset});
			const Vector3 offset = entity.getPosition() - entity.getPosition().floor();
			renderer.write(textures[block].getColour(offset));
		}
		renderer.writeLine();
	}
	renderer.flush();
}

void io::IoHandler::readInput(engine::EntityInterface& entity) {
	input.read(inputBuffer);
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
				entity.setMovementDirection({(double)direction.right - direction.left, (double)direction.up - direction.down});
			}
		}
		else if (data.index() == 1) {
			MouseButtons mouseButtons = std::get<1>(data);
			if (hasFlag(mouseButtons, RIGHT)) {
				entity.placeBlock(player.getSelectedItem());
			}
		}
		else if (data.index() == 2) {
			Point point = std::get<2>(data);
			Orientation rotation = { ((int32_t)point.x - mousePointer.x) * sensitivity, ((int32_t)point.y - mousePointer.y) * sensitivity };
			mousePointer = point;
			entity.rotate(rotation);
		}
	}
	inputBuffer.clear();
}

