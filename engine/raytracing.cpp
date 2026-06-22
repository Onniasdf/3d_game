#include "../datastructures/vector3.hpp"
#include "raytracing.hpp"

RayStateMachine::RayStateMachine(const Vector3 &start, const Vector3 &direction) {
	this->direction = direction;
	lastPosition = start;
	position = start;
	const Sign3 directionSign = direction.sign();
	sign = Vector3(directionSign);
	target = start.roundTowards(directionSign);
}

Vector3 RayStateMachine::step() {
	const Vector3 steps = (target - position) / direction;
	const Vector3::Axis minType = steps.minAxis();
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