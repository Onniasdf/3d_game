#pragma once
#include "../datastructures/vector3.hpp"
#include "../datastructures/orientation.hpp"
#include <cmath>
#include <cstdint>

namespace engine {
    struct Environment {
        double gravity;
        double jumpSpeed;
        double movementAcceleration;
        double friction;

        static Environment calculateFromPerSecond(const uint32_t ticks, const double gravity, const double movementSpeed, const double jumpHeight) {
            Environment physics{};
            physics.gravity = gravity / ticks;
            physics.jumpSpeed = std::sqrt(physics.gravity * jumpHeight);
            physics.movementAcceleration = movementSpeed / ticks;
            physics.friction = 1;
            return physics;
        }
    };

    struct EntityState {
        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration;

		double movementDirection{};
        Orientation orientation;

        void update(const double friction) {
            position += velocity;
            velocity += acceleration;
            acceleration *= 1 - friction;
        }

        explicit EntityState(const Vector3& position) : position(position) {}
    };
}
