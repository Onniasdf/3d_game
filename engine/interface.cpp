#include "interface.hpp"
#include "physics.hpp"
#include "raytracing.hpp"
#include <cmath>
#include "../datastructures/orientation.hpp"
#include "../datastructures/vector3.hpp"
#include <optional>

static RayEnd seekBlock(const engine::LimitedBlockWorld& world, const Vector3& start, const Vector3& direction) {
    RayStateMachine stateMachine{start, direction};
    Vector3 position = stateMachine.step();
    while (!world.get(position).has_value()) {
        position = stateMachine.step();
    }
    return stateMachine.end();
}

void engine::EntityInterface::jump() const {
    entity.launchVertical(physics.jumpSpeed);
}

void engine::EntityInterface::rotate(const Orientation orientationChange) const {
    entity.rotateView(orientationChange);
    entity.updateMovementDirection();
}

void engine::EntityInterface::setMovementDirection(const Vector2& direction) const {
    if (direction.length() == 0) {
		entity.stop();
		return;
    }
    entity.rotateMovement(direction);
    entity.updateMovementDirection();
}

void engine::EntityInterface::placeBlock(uint16_t id) const {
    auto [start, direction] = entity.getView({});
    auto [hit, lastBlock] = seekBlock(world, start, direction);
    world.set(lastBlock, id);
}

engine::BlockOffset engine::EntityInterface::findBlock(const Orientation offset) const {
    auto [start, direction] = entity.getView(offset);
    auto [hit, lastBlock] = seekBlock(world, start, direction);
    const uint16_t block = world.get(hit).value();
    const Vector3 blockOffset = hit - hit.floor();
    return {block, blockOffset};
}

void engine::WorldInterface::end() const {
    running = false;
}

size_t engine::WorldInterface::addEntity(const Vector3& position, const Vector3& hitbox) const {
    const EntityInformation entity{EntityState(position), hitbox, physics.movementAcceleration};
    const size_t id = entities.size();
    entities.push_back(entity);
    return id;
}

std::optional<engine::EntityInterface> engine::WorldInterface::getEntity(const size_t id) const {
    if (id >= entities.size()) {
        return {};
    }
    EntityInformation& entityInformation = entities[id];
    const Entity entity{entityInformation};
    EntityInterface entityInterface = {world, entity, physics};
    return {entityInterface};
}
