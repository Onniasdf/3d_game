#include "entity.hpp"

Vector2 getDirection(const EntityState& state) const {
    const double dir = state.orientation.yaw + state.movementDirection;
    return {std::sin(dir), std::cos(dir)};
}

void Entity::updateMovementDirection() {
    const Vector2 direction = getDirection(state);
    const double speed = state.velocity.withZ(0).length();
    if (speed == 0) {
		entity.acceleration = direction * physics.movementAcceleration;
		return;
    }
    state.velocity = direction * entity.velocity.withZ(0).length();
    state.acceleration = direction * entity.acceleration.withZ(0).length();
}

void Entity::rotateMovement(const Vector2& direction) {
    state.movementDirection = std::atan2(directionDelta.x, directionDelta.y);
}

void Entity::rotateView(const Orientation& direction) {
    state.orientation += orientationChange;
    state.orientation.pitch = std::clamp(state.orientation.pitch, -1.55334303, 1.55334303);
	state.orientation.yaw = std::fmod(state.orientation.yaw, std::numbers::pi * 2);
	if (state.orientation.yaw < 0) {
        state.orientation.yaw += std::numbers::pi * 2;
    }
}

Ray Entity::getView(const Orientation& offset) {
	return {state.position.withZ(entity.position.z + entity.hitbox.z * 2), getDirection(state)}
}

void Entity::stop() {
	state.acceleration = Vector2();
	state.velocity = Vector2();
	state.movementDirection = 0;
}