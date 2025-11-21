#ifndef INC_3D_GAME_ENTITY_HPP
#define INC_3D_GAME_ENTITY_HPP
#include "../datastructures/vector3.hpp"
#include "../datastructures/orientation.hpp"
#include <cmath>

namespace engine {
    struct Physics {
        double gravity;
        double jumpSpeed;
        double movementAcceleration;
        double friction;

        static Physics calculateFromPerSecond(const uint32_t ticks, const double gravity, double movementSpeed, const double jumpHeight) {
            Physics physics{};
            physics.gravity = gravity / ticks;
            physics.jumpSpeed = std::sqrt(physics.gravity * jumpHeight);
            physics.movementAcceleration = movementSpeed / ticks;
            physics.friction = 1;
            return physics;
        }
    };

    enum MovementState {
        STILL,
        MOVING,
    };

    struct Entity {
        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration;
        Vector3 hitbox;

        MovementState movementState = STILL;
        Vector2 direction;
        Orientation orientation;

        void update(const double friction) {
            position += velocity;
            velocity += acceleration;
            acceleration *= 1 - friction;
        }
    };
}

#endif
