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
		switch (data.index()) {
			case io::KEYBOARD:
				auto [key, down] = std::get<io::KEYBOARD>(data);
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
			case io::MOUSE:
				if (const MouseButtons mouseButtons = std::get<io::MOUSE>(data); mouseButtons.right) {
					entity.placeBlock(player.getSelectedItem());
				}
			case io::MOUSE_POSITION:
				const Point point = std::get<io::MOUSE_POSITION>(data);
				const Orientation rotation((static_cast<int32_t>(point.x) - static_cast<int32_t>(mousePointer.x)) * sensitivity, (static_cast<int32_t>(point.y) - static_cast<int32_t>(mousePointer.y)) * sensitivity);
				mousePointer = point;
				entity.rotate(rotation);
			case io::SPECIAL:
				if (const SpecialKey specialKey = std::get<io::SPECIAL>(data); specialKey == ESCAPE) {
					quit = true;
				}
		}
	}
	inputBuffer.clear();
}

