#include "interface.hpp"
#include "physics.hpp"
#include "raytracing.hpp"
#include <numbers>
#include <cstdint>
#include <cmath>
#include "../datastructures/orientation.hpp"
#include "../datastructures/vector3.hpp"
#include "../datastructures/rgb_colour.hpp"
#include <optional>
#include <algorithm>

void engine::EntityInterface::jump() {
    if (entity.velocity.z == 0) {
        entity.velocity.z = physics.jumpSpeed;
    }
}

void engine::EntityInterface::rotate(const Orientation orientationChange) {
    entity.orientation += orientationChange;
    entity.orientation.pitch = std::clamp(entity.orientation.pitch, -1.55334303, 1.55334303);
	entity.orientation.yaw = std::fmod(entity.orientation.yaw, std::numbers::pi * 2);
    const Vector2 dir = {std::cos(entity.orientation.yaw), std::sin(entity.orientation.yaw)};
    entity.direction = dir;
    (dir * entity.velocity.withZ(0).length()).combineWith(entity.velocity);
    (dir * entity.acceleration.withZ(0).length()).combineWith(entity.acceleration);
}

void engine::EntityInterface::setMovementDirection(const Vector2& directionDelta) {
	const Vector2 sideways = { -entity.direction.y, entity.direction.x };
    const Vector2 direction = entity.direction * directionDelta.y + sideways * directionDelta.x;
    const double directionLength = direction.length();
    if (directionLength == 0) {
        entity.acceleration.x = 0;
		entity.acceleration.y = 0;
		entity.velocity.x = 0;
        entity.velocity.y = 0;
        return;
    }
    const Vector2 directionUnit = direction / directionLength;
    const double speed = entity.velocity.withZ(0).length();
    if (speed == 0) {
		double z = entity.acceleration.x;
		entity.acceleration = directionUnit * physics.movementAcceleration;
        entity.acceleration.z = z;
		return;
    }
    (directionUnit * entity.velocity.withZ(0).length()).combineWith(entity.velocity);
	(directionUnit * entity.acceleration.withZ(0).length()).combineWith(entity.acceleration);
}


void engine::EntityInterface::placeBlock(uint16_t id) {
    RayEnd end = castRay(world, entity.position, entity.direction);
    world.set(end.lastBlock, id);
}


uint16_t engine::EntityInterface::findBlock(const Orientation offset) {
	const Orientation angle = entity.orientation + offset;
    Vector3 dir = angle.getDirection();
    RayEnd end = castRay(world, entity.position.withZ(entity.position.z + entity.hitbox.z), dir);
    uint16_t block = world.get(end.hit).value();
    return block;
}

void engine::WorldInterface::end() const {
    running = false;
}

size_t engine::WorldInterface::addEntity(const Vector3& position, const Vector3& hitbox) const {
    Entity entity{};
    entity.position = position;
    entity.hitbox = hitbox;
    const size_t id = entities.size();
    entities.push_back(entity);
    return id;
}

std::optional<engine::EntityInterface> engine::WorldInterface::getEntity(size_t id) {
    if (id >= entities.size()) {
        return {};
    }
    Entity& entity = entities[id];
    EntityInterface entityInterface = {world, entity, physics};
    return {entityInterface};
}