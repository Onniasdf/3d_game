#pragma once

#include "../datastructures/vector3.hpp"

struct RayEnd {
	Vector3 hit;
	Vector3 lastBlock;
};

class RayStateMachine {
	Vector3 sign;
	Vector3 lastPosition;
	Vector3 position;
	Vector3 target;
	Vector3 direction;

public:
	RayStateMachine(const Vector3 &start, const Vector3 &direction);
	Vector3 step();
	[[nodiscard]] RayEnd end() const;
};

