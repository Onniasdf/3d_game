#include "io.hpp"
#include "../datastructures/rgb_colour.hpp"
#include <cctype>

template<engine::Interactable TWorld>
void io::IoHandler::writeOutput(engine::EntityInterface<TWorld>& player) {
	renderer.startFrame();
	for (double pitchOffset = -orientationLimit.pitch; pitchOffset <= orientationLimit.pitch; pitchOffset += orientationDelta.pitch) {
		for (double yawOffset = -orientationLimit.yaw; yawOffset <= orientationLimit.yaw; yawOffset += orientationDelta.yaw) {
			const RgbColour colour = player.getColour({yawOffset, pitchOffset});
			renderer.write(colour);
		}
		renderer.writeLine();
	}
	renderer.flush();
}

template<engine::Interactable TWorld>
void io::IoHandler::readInput(engine::EntityInterface<TWorld>& player) {
	input.read(inputBuffer);
	for (auto& data : inputBuffer) {
		if (data.index() == 0) {
			auto [key, down] = std::get<0>(data);
			Direction start = direction;
			switch (static_cast<char>(std::tolower(static_cast<unsigned char>(key)))) {
				case 'w':
					direction.up = down;
					break;
				case 's':
					direction.down = down;
					break;
				case 'd':
					direction.right = down;
					break;
				case 'a':
					direction.left = down;
					break;
				case ' ':
					player.jump();
					break;
				default:
					if (key >= '0' && key <= '9') {
						const uint32_t block = key - '0';
						currentBlock = block;
					}
			}
			if (start != direction) {
				player.setMovement(direction);
			}
		}
		else if (data.index() == 1) {
			MouseButtons mouseButtons = std::get<1>(data);
			if (hasFlag(mouseButtons, RIGHT)) {
				player.placeBlock(currentBlock);
			}
		}
	}
	inputBuffer.clear();
}

