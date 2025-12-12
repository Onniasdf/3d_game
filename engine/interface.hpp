#pragma once
#include "../datastructures/rgb_colour.hpp"
#include "../datastructures/orientation.hpp"
#include "physics.hpp"
#include <vector>
#include "block_world.hpp"
#include "../datastructures/vector3.hpp"
#include <cstdint>
#include <optional>

namespace engine {
    struct BlockOffset {
        uint16_t block;
        Vector3 offset;
    };

    class EntityInterface {
        LimitedBlockWorld& world;
        Entity& entity;
        const Physics& physics;

    public:
        EntityInterface(LimitedBlockWorld& world, Entity& entity, const Physics& physics) : world(world), entity(entity), physics(physics) {}

        void jump();

        void rotate(Orientation orientationChange);

        void setMovementDirection(const Vector2& direction);

        void placeBlock(uint16_t id);

        Vector3 getPosition() const {
			return entity.position;
        }

        BlockOffset findBlock(Orientation offset);
    };


    class WorldInterface {
        LimitedBlockWorld& world;
        bool& running;
        std::vector<Entity>& entities;
        const Physics& physics;


    public:
        WorldInterface(LimitedBlockWorld& world, bool& running, std::vector<Entity>& entities, const Physics& physics) : world(world), running(running), entities(entities), physics(physics) {}
        
        void end() const;

        [[nodiscard]] size_t addEntity(const Vector3& position, const Vector3& hitbox) const;

        [[nodiscard]] std::optional<EntityInterface> getEntity(size_t id);
    };
}
