#pragma once
#include "../datastructures/rgb_colour.hpp"
#include "../datastructures/vector3.hpp"

namespace io {
	class Texture {
		RgbColour colour;

	public:
		Texture(const RgbColour& colour) : colour(colour) {}
		RgbColour getColour(const Vector3& offset) const {
			return colour;
		}
	};
}