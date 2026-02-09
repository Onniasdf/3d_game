#include "physics.hpp"
#include "../datastructures/vector3.hpp"
#include "../datastructures/orientation.hpp"

namespace engine {
    struct Ray {
        const Vector3 direction;
        const Vector3 start;
    }
    class Entity {
        EntityState state;
        void updateMovementDirection();
        void stop();
        void rotateMovement(const Vector2& direction);
        void rotateView(const Orientation& direction);
        Ray getView(const Orientation& offset);
    }
}