#ifndef INC_3D_GAME_RAYTRACING_HPP
#define INC_3D_GAME_RAYTRACING_HPP

#include "block_world.hpp"
#include "../datastructures/vector3.hpp"

struct RayEnd {
	Vector3 hit;
	Vector3 lastBlock;
};

RayEnd castRay(const engine::LimitedBlockWorld& world, const Vector3& start, const Vector3& direction);

#endif
