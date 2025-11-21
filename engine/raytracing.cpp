#include "../datastructures/vector3.hpp"
#include "block_world.hpp"
#include "raytracing.hpp"
#include <cmath>


double min(const Vector3& vec) {
	const Vector3 abs = vec.abs();
	double min = vec.x;
	double minAbs = abs.x;
	if (abs.y < minAbs) {
		min = vec.y;
		minAbs = abs.y;
	}
	if (abs.z < minAbs) {
		min = vec.z;
	}
	return min;
}

double getTargetCoordinate(const double pos, const double sign) {
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

RayEnd castRay(const engine::LimitedBlockWorld& world, const Vector3& start, const Vector3& direction) {
	const Vector3 sign = direction.sign();
	Vector3 lastPos = start;
	Vector3 position = start;
	while (!world.get(position).has_value()) {
		Vector3 target = {getTargetCoordinate(position.x, sign.x), getTargetCoordinate(position.y, sign.z), getTargetCoordinate(position.z, sign.z) };
		lastPos = position;
		const double mul = min((target - position) * sign / direction);
		position += direction * std::abs(mul);
	}
	return {position, lastPos};
}
