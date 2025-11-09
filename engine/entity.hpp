#ifndef INC_3D_GAME_ENTITY_HPP
#define INC_3D_GAME_ENTITY_HPP
#include "../datastructures/vector3.hpp"
#include "../datastructures/orientation.hpp"

namespace engine {
    struct Physics {
        double gravity;
        double jumpSpeed;
        double movementAcceleration;
        double friction;

        static Physics calculateFromMetersPerSecond(uint32_t ticks, double gravity, double movementSpeed) {

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
        Vector3 direction;
        Orientation orientiation;

        void update(const Vector3& force, const double friction) {
            position += velocity;
            velocity += acceleration + force;
            acceleration *= 1 - friction;
        }
    };
}

#endif
