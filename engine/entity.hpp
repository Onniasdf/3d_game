#ifndef INC_3D_GAME_ENTITY_HPP
#define INC_3D_GAME_ENTITY_HPP
#include "../datastructures/Vector3.hpp"

namespace engine {
    struct Physics {
        double gravity;
        double jumpSpeed;
        double movementAcceleration;
        double friction;
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
        double pitch = 0;
        double yaw = 0;

        void update(const Vector3& force, const double friction) {
            position += velocity;
            velocity += acceleration + force;
            acceleration *= 1 - friction;
        }
    };
}

#endif
