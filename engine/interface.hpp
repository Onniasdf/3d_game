#ifndef INC_3D_GAME_INTERFACE_HPP
#define INC_3D_GAME_INTERFACE_HPP
#include "world.hpp"
#include "../datastructures/rgb_colour.hpp"
#include "../datastructures/orientation.hpp"
#include "entity.hpp"

namespace engine {
    template <typename TWorld>
    requires Interactable<TWorld>
    class EntityInterface {
        TWorld& world;
        const RgbColour* colourMap;
        Entity& entity;
        const Physics& physics;

    public:
        EntityInterface(TWorld& world, const RgbColour* colourMap, Entity& entity, const Physics& physics) : world(world), colourMap(colourMap), entity(entity), physics(physics) {}

        void jump() const {
            if (entity.velocity.z == 0) {
                entity.velocity.z = physics.jumpSpeed;
            }
        }

        void rotate(Orientation orientationChange) const {
            entity.orientiation.yaw += orientationChange.yaw;
            entity.orientiation.pitch += orientationChange.pitch;
            Orientation horizontalOrientation{entity.orientiation.yaw, 0};
            const Vector3 dir = horizontalOrientation.getDirection();
            const double z = entity.velocity.z;
            entity.velocity = dir * entity.velocity.withZ(0).length();
            entity.velocity.z = z;
            entity.acceleration = dir * entity.acceleration.length();
        }

        void setMoving(const MovementState state) const {
            if (state == entity.movementState) return;
            entity.movementState = state;
            const Vector3 acceleration = entity.orientiation.getDirection() * physics.movementAcceleration;
            if (state == MOVING) {
                entity.acceleration = acceleration;
            } else {
                entity.acceleration = -(acceleration - entity.acceleration);
            }
        }

        RgbColour getColor(Orientation offset) {
            const double pitch = entity.pitch + pitchOffset;
            const double yaw = entity.yaw + yawOffset;
            Vector3 dir = Vector3::fromAngle(yaw, pitch);
            const size_t block = castRay(world, entity.position, dir);
            return colourMap[block];
        }
    };

    template <typename TWorld>
    requires Interactable<TWorld>
    class WorldInterface {
        TWorld& world;
        const RgbColour* colourMap;
        bool& running;
        std::vector<Entity>& entities;
        const Physics& physics;


    public:
        WorldInterface(TWorld& world, const RgbColour* colourMap, bool& running, std::vector<Entity>& entities, const Physics& physics) : world(world), colourMap(colourMap), running(running), entities(entities), physics(physics) {}
        
        void end() const {
            running = false;
        }

        [[nodiscard]] size_t addEntity(Vector3 position, Vector3 hitbox) const {
            Entity entity{};
            entity.position = position;
            entity.hitbox = hitbox;
            const size_t id = entities.size();
            entities.push_back(entity);
            return id;
        }

        [[nodiscard]] std::optional<EntityInterface<TWorld>> getEntity(const size_t id) {
            if (id >= entities.size()) {
                return {};
            }
            Entity& entity = entities[id];
            EntityInterface<TWorld> entityInterface = {world, colourMap, entity, physics};
            return {entityInterface};
        }
    };
}

#endif
