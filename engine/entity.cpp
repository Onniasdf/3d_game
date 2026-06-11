#include "entity.hpp"

Vector2 getDirection(const engine::EntityState& state) {
    const double dir = state.orientation.yaw + state.movementDirection;
    return {std::sin(dir), std::cos(dir)};
}

void engine::Entity::updateMovementDirection() const {
    const Vector2 direction = getDirection(information.state);
    if (information.state.velocity.withZ(0).length() == 0) {
		information.state.acceleration = direction * information.acceleration;
		return;
    }
    information.state.velocity = direction * information.state.velocity.withZ(0).length();
    information.state.acceleration = direction * information.state.acceleration.withZ(0).length();
}

void engine::Entity::rotateMovement(const Vector2& direction) const {
    information.state.movementDirection = std::atan2(direction.x, direction.y);
}

void engine::Entity::rotateView(const Orientation& direction) const {
    information.state.orientation += direction;
    information.state.orientation.pitch = std::clamp(information.state.orientation.pitch, -std::numbers::pi / 2, std::numbers::pi / 2);
	information.state.orientation.yaw = std::fmod(information.state.orientation.yaw, std::numbers::pi * 2);
	if (information.state.orientation.yaw < 0) {
        information.state.orientation.yaw += std::numbers::pi * 2;
    }
}

void engine::Entity::launchVertical(const double acceleration) const {
	if (information.state.velocity.z == 0) {
		information.state.velocity.z = acceleration;
		information.state.position.z += acceleration;
	}
}

engine::Ray engine::Entity::getView(const Orientation& offset) const {
	return {information.state.position.withZ(information.state.position.z + information.hitbox.z), (information.state.orientation + offset).getDirection()};
}

void engine::Entity::stop() const {
	information.state.acceleration = Vector2();
	information.state.velocity = Vector2();
	information.state.movementDirection = 0;
}
