#include "../datastructures/rgb_colour.hpp"
#include "../datastructures/vector3.hpp"
#include "textures.hpp"


constexpr int PRESICION = 10;

static RgbColour getBaseColour(game::Block type) {
	switch (type) {
	case game::RED:
		return { 255, 0, 0 };
	case game::GREEN:
		return { 0, 255, 0 };
	case game::BLUE:
		return { 0, 0, 255 };
	case game::YELLOW:
		return { 255, 255, 0 };
	case game::MAGENTA:
		return { 255, 0, 255 };
	case game::CYAN:
		return { 0, 255, 255 };
	case game::GRAY:
		return { 128, 128, 128 };
	case game::ORANGE:
		return { 255, 128, 0 };
	case game::PURPLE:
		return { 128, 0, 128 };
	case game::GRASS:
		return { 0, 255, 0 };
	default:
		return {};
	}
}

RgbColour game::resolveColour(Block type, const Vector3& offset) {
	const Vector3 pos = (offset.min((Vector3(1, 1, 1) - offset).abs()) * PRESICION).floor();
	const bool nx = (pos.x == 0);
	const bool ny = (pos.y == 0);
	const bool nz = (pos.z == 0);

	int zeroCount = (nx ? 1 : 0) + (ny ? 1 : 0) + (nz ? 1 : 0);
	if (zeroCount >= 2 && type < 10) {
		return {};
	}
	return getBaseColour(type);
}
