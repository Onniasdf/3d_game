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
	else {
		const double target = std::floor(pos);
		if (target == pos) {
			return target - 1;
		}
		return target;
	}
}

enum CoordinateType {
	X, Y, Z
};

static CoordinateType minCoordinate(Vector3& vec) {
	double min = vec.x;
	CoordinateType minType = X;
	if (vec.y < min) {
		min = vec.y;
		minType = Y;
	}
	if (vec.z < min) {
		minType = Z;
	}
	return minType;
}

RayEnd castRay(const engine::LimitedBlockWorld& world, const Vector3& start, const Vector3& direction) {
	const Vector3 sign = direction.sign();
	Vector3 lastPosition = start;
	Vector3 position = start;
	Vector3 target = {getTargetCoordinate(start.x, sign.x), getTargetCoordinate(start.y, sign.y), getTargetCoordinate(start.z, sign.z) };
	while (!world.get(position).has_value()) {
		Vector3 steps = (target - position) / direction;
		CoordinateType minType = minCoordinate(steps);
		double minSteps = 0;
		switch (minType) {
		case X:
			target.x += sign.x;
			minSteps = steps.x;
			break;
		case Y:
			target.y += sign.y;
			minSteps = steps.y;
			break;
		case Z:
			target.z += sign.z;
			minSteps = steps.z;
			break;
		}
		lastPosition = position;
		position += direction * minSteps;
	}
	return {position, lastPosition};
}
