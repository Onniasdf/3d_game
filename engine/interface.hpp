#pragma once
#include "../datastructures/orientation.hpp"
#include "physics.hpp"
#include "entity.hpp"
#include "block_world.hpp"
#include "../datastructures/vector3.hpp"
#include <optional>
#include <vector>

namespace engine {
    struct BlockOffset {
        uint16_t block{};
        Vector3 offset;
    };

    class EntityInterface {
        LimitedBlockWorld& world;
        Entity entity;
        const Environment& physics;

    public:
        EntityInterface(LimitedBlockWorld& world, const Entity entity, const Environment& physics) : world(world), entity(entity), physics(physics) {}

        void jump() const;

        void rotate(Orientation orientationChange) const;

        void setMovementDirection(const Vector2& direction) const;

        void placeBlock(uint16_t id) const;

        [[nodiscard]] BlockOffset findBlock(Orientation offset) const;
    };


    class WorldInterface {
        LimitedBlockWorld& world;
        bool& running;
        std::vector<EntityInformation>& entities;
        const Environment& physics;


    public:
        WorldInterface(LimitedBlockWorld& world, bool& running, std::vector<EntityInformation>& entities, const Environment& physics) : world(world), running(running), entities(entities), physics(physics) {}
        
        void end() const;

        [[nodiscard]] size_t addEntity(const Vector3& position, const Vector3& size) const;

        [[nodiscard]] std::optional<EntityInterface> getEntity(size_t id) const;
    };
}
