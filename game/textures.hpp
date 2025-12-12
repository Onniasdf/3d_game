#pragma once
#include "../datastructures/rgb_colour.hpp"
#include "../datastructures/vector3.hpp"
#include <cstdint>

namespace game
{
	enum Block : uint16_t {
		BLACK,
		RED,
		GREEN,
		BLUE,
		YELLOW,
		MAGENTA,
		CYAN,
		GRAY,
		ORANGE,
		PURPLE,
		GRASS
	};
	RgbColour resolveColour(Block type, const Vector3& offset);
}