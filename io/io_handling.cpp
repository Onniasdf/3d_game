#include "io_handling.hpp"
#include "../engine/interface.hpp"
#include "../game/textures.hpp"
#include <variant>
#include <cctype>
#include "../datastructures/vector3.hpp"
#include "../datastructures/orientation.hpp"
#include "input.hpp"
#include "../game/player.hpp"

void io::IoHandler::writeOutput(const engine::EntityInterface& entity) {
	renderer.startFrame();
	for (double pitchOffset = orientationLimit.pitch; pitchOffset >= -orientationLimit.pitch; pitchOffset -= orientationDelta.pitch) {
		for (double yawOffset = -orientationLimit.yaw; yawOffset <= orientationLimit.yaw; yawOffset += orientationDelta.yaw) {
			const auto [block, offset] = entity.findBlock({yawOffset, pitchOffset});
			renderer.write(game::resolveColour(static_cast<game::Block>(block), offset));
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
			if (game::Direction direction = player.getMovementDirection(); start != direction) {
				entity.setMovementDirection({static_cast<double>(direction.right) - static_cast<double>(direction.left), static_cast<double>(direction.up) - static_cast<double>(direction.down)});
			}
		}
		else if (data.index() == 1) {
			if (const MouseButtons mouseButtons = std::get<1>(data); mouseButtons.right) {
				entity.placeBlock(player.getSelectedItem());
			}
		}
		else if (data.index() == 2) {
			const Point point = std::get<2>(data);
			const Orientation rotation((static_cast<int32_t>(point.x) - static_cast<int32_t>(mousePointer.x)) * sensitivity, (static_cast<int32_t>(point.y) - static_cast<int32_t>(mousePointer.y)) * sensitivity);
			mousePointer = point;
			entity.rotate(rotation);
		}
		else if (data.index() == 3) {
			if (const SpecialKey specialKey = std::get<3>(data); specialKey == ESCAPE) {
				quit = true;

			}
		}
	}
	inputBuffer.clear();
}

