#ifndef ORIENTATION_HPP
#define ORIENTATION_HPP

#include "vector3.hpp"

struct Orientation {
    double yaw = 0, pitch = 0;

    Orientation(double yaw, double pitch) : yaw(yaw), pitch(pitch) {}
    Orientation() = default;

    Vector3 getDirection() {
        Vector3 dir;
        dir.x = std::cos(pitch) * std::sin(yaw);
        dir.y = std::sin(pitch);
        dir.z = std::cos(pitch) * std::cos(yaw);
        return dir;
    }
};

#endif
