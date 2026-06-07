#include "../datastructures/vector3.hpp"
#include "block_world.hpp"
#include "raytracing.hpp"
#include <cmath>



static double getTargetCoordinate(const double pos, const double sign) {
	if (sign == 1) {
		const double target = std::ceil(pos);
		if (target == pos) {
			return target + 1;
		}
		return target;
	}
	const double target = std::floor(pos);
	if (target == pos) {
		return target - 1;
	}
	return target;
}


static Vector3::Axis minCoordinate(const Vector3& vec) {
	double min = vec.x;
	Vector3::Axis minType = Vector3::X;
	if (vec.y < min) {
		min = vec.y;
		minType = Vector3::Y;
	}
	if (vec.z < min) {
		minType = Vector3::Z;
	}
	return minType;
}

RayStateMachine::RayStateMachine(const Vector3 &start, const Vector3 &direction) {
	this->direction = direction;
	lastPosition = start;
	position = start;
	sign = direction.sign();
	target = {getTargetCoordinate(start.x, sign.x), getTargetCoordinate(start.y, sign.y), getTargetCoordinate(start.z, sign.z) };
}

Vector3 RayStateMachine::step() {
	const Vector3 steps = (target - position) / direction;
	const Vector3::Axis minType = minCoordinate(steps);
	double minSteps = 0;
	switch (minType) {
		case Vector3::X:
			target.x += sign.x;
			minSteps = steps.x;
			break;
		case Vector3::Y:
			target.y += sign.y;
			minSteps = steps.y;
			break;
		case Vector3::Z:
			target.z += sign.z;
			minSteps = steps.z;
			break;
	}
	lastPosition = position;
	position += direction * minSteps;
	return position;
}

RayEnd RayStateMachine::end() const {
	return {position, lastPosition};
}