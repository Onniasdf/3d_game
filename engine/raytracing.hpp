#pragma once

#include "block_world.hpp"
#include "../datastructures/vector3.hpp"

struct RayEnd {
	Vector3 hit;
	Vector3 lastBlock;
};

RayEnd castRay(const engine::LimitedBlockWorld& world, const Vector3& start, const Vector3& direction);

