#pragma once

#include "vector3.hpp"
#include <cmath>

struct Orientation {
    double yaw = 0, pitch = 0;

    Orientation(const double yaw, const double pitch) : yaw(yaw), pitch(pitch) {}
    Orientation() = default;

    [[nodiscard]] Vector3 getDirection() const {
        const Vector3 dir{std::cos(pitch) * std::sin(yaw),std::cos(pitch) * std::cos(yaw),std::sin(pitch)};
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
