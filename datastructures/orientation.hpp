#pragma once

#include "vector3.hpp"
#include <cmath>

struct Orientation {
    double yaw = 0, pitch = 0;

    Orientation(double yaw, double pitch) : yaw(yaw), pitch(pitch) {}
    Orientation() = default;

    Vector3 getDirection() const {
        Vector3 dir{std::cos(pitch) * std::sin(yaw),std::cos(pitch) * std::cos(yaw),std::sin(pitch)};
        return dir;
    }

    Orientation operator+(const Orientation& other) const {
        return {yaw + other.yaw, pitch + other.pitch};
    }

    void operator+=(const Orientation& other) {
        yaw += other.yaw;
        pitch += other.pitch;
    }
};
