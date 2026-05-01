#include "interface.hpp"
#include "physics.hpp"
#include "raytracing.hpp"
#include <numbers>
#include <cstdint>
#include <cmath>
#include "../datastructures/orientation.hpp"
#include "../datastructures/vector3.hpp"
#include <optional>
#include <algorithm>

void engine::EntityInterface::jump() {
    if (entity.velocity.z == 0) {
        entity.velocity.z = physics.jumpSpeed;
        entity.position.z += physics.jumpSpeed;
    };
}

void engine::EntityInterface::rotate(const Orientation orientationChange) {
    entity.orientation += orientationChange;
    entity.orientation.pitch = std::clamp(entity.orientation.pitch, -1.55334303, 1.55334303);
	entity.orientation.yaw = std::fmod(entity.orientation.yaw, std::numbers::pi * 2);
	if (entity.orientation.yaw < 0) {
        entity.orientation.yaw += std::numbers::pi * 2;
    }
    Vector3 dir = entity.getDirection();
    entity.velocity = dir * entity.velocity.withZ(0).length();
    entity.acceleration = dir * entity.acceleration.withZ(0).length();
}

void engine::EntityInterface::setMovementDirection(const Vector2& directionDelta) {
    const double directionLength = directionDelta.length();
    if (directionLength == 0) {
        entity.acceleration = Vector2();
        entity.velocity = Vector2();
        entity.movementDirection = 0;
        return;
    }
    entity.movementDirection = std::atan2(directionDelta.x, directionDelta.y);
    const Vector2 direction = entity.getDirection();
    const double speed = entity.velocity.withZ(0).length();
    if (speed == 0) {
		entity.acceleration = direction * physics.movementAcceleration;
		return;
    }
    entity.velocity = direction * entity.velocity.withZ(0).length();
    entity.acceleration = direction * entity.acceleration.withZ(0).length();
}


void engine::EntityInterface::placeBlock(uint16_t id) {
    RayEnd end = castRay(world, entity.position.withZ(entity.position.z + entity.hitbox.z * 2), entity.orientation.getDirection());
    world.set(end.lastBlock, id);
}

engine::BlockOffset engine::EntityInterface::findBlock(const Orientation offset) {
	const Orientation angle = entity.orientation + offset;
    Vector3 dir = angle.getDirection();
    RayEnd end = castRay(world, entity.position.withZ(entity.position.z + entity.hitbox.z * 2), dir);
    uint16_t block = world.get(end.hit).value();
    Vector3 blockOffset = end.hit - end.hit.floor();
    return { block, blockOffset };
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