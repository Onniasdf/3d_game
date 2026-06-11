#pragma once
#include "physics.hpp"
#include "../datastructures/vector3.hpp"
#include "../datastructures/orientation.hpp"

namespace engine {
    struct Ray {
        const Vector3 start;
        const Vector3 direction;
    };
    struct EntityInformation {
        EntityState state;
        Vector3 hitbox;
        double acceleration{};

        EntityInformation(const EntityState& state, const Vector3& hitbox, const double acceleration) : state(state), hitbox(hitbox), acceleration(acceleration) {}
    };
    class Entity {
        EntityInformation& information;
        public:
        void updateMovementDirection() const;
        void rotateMovement(const Vector2& direction) const;
        void stop() const;
        void rotateView(const Orientation& direction) const;
        void launchVertical(double acceleration) const;
        [[nodiscard]] Ray getView(const Orientation& offset) const;

        explicit Entity(EntityInformation& entity) : information(entity) {};
    };
}