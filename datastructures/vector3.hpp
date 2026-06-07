#pragma once

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <algorithm>

#include "vector2.hpp"


struct Vector3 {
    double x = 0, y = 0, z = 0;

    enum Axis {
        X, Y, Z
    };

    Vector3(const double x, const double y, const double z) : x(x), y(y), z(z) {}
    explicit Vector3(const Vector2& vec2) : x(vec2.x), y(vec2.y) {}
    Vector3() = default;

    [[nodiscard]] double get(const Axis axis) const {
        switch (axis) {
            case X:
                return x;
            case Y:
                return y;
            case Z:
                return z;
        }
        return 0;
    }

    Vector3 operator+(const Vector3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }
    Vector3 operator-(const Vector3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    Vector3 operator-() const {
        return {-x, -y, -z};
    }

    Vector3 operator*(const double scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }

    Vector3 operator*(const Vector3& other) const {
        return {x * other.x, y * other.y, z * other.z};
    }

    Vector3 operator/(const double scalar) const {
        return {x / scalar, y / scalar, z / scalar};
    }

    Vector3 operator/(const Vector3& other) const {
        return {x / other.x, y / other.y, z / other.z};
    }

    void operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    void operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    [[nodiscard]] Vector3 clamp(const double min, const double max) const {
        return {std::clamp(x, min, max), std::clamp(y, min, max), std::clamp(z, min, max)};
	}


    void operator*=(const double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }
    void operator/=(const double scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    }

    Vector3 operator=(const Vector2& other) {
        x = other.x;
        y = other.y;
        return *this;
    }


    [[nodiscard]] double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    [[nodiscard]] double lengthSquared() const {
        return x * x + y * y + z * z;
    }

    [[nodiscard]] Vector3 floor() const {
        return {std::floor(x), std::floor(y), std::floor(z)};
    }

    [[nodiscard]] Vector3 ceil() const {
        return {std::ceil(x), std::ceil(y), std::ceil(z)};
    }

    [[nodiscard]] Vector3 round() const {
        return {std::round(x), std::round(y), std::round(z)};
    }

    [[nodiscard]] Vector3 sign() const {
        return {getSign(x), getSign(y), getSign(z)};
    }

    [[nodiscard]] Vector3 abs() const {
        return {std::abs(x), std::abs(y), std::abs(z)};
    }

    [[nodiscard]] double max() const {
        return std::max(x, std::max(y, z));
    }

    [[nodiscard]] double min() const {
        return std::min(x, std::min(y, z));
    }

    [[nodiscard]] Vector3 min(const Vector3& other) const {
        return {std::min(x, other.x), std::min(y, other.y),  std::min(z, other.z)};
    }
    [[nodiscard]] Vector3 max(const Vector3& other) const {
        return {std::max(x, other.x), std::max(y, other.y),  std::max(z, other.z)};
	}

    [[nodiscard]] Vector3 withX(const double otherX) const {
        return {otherX, y, z};
    }

    [[nodiscard]] Vector3 withY(const double otherY) const {
        return {x, otherY, z};
    }

    [[nodiscard]] Vector3 withZ(const double otherZ) const {
        return {x, y, otherZ};
    }

private:
    static double getSign(double value) {
        if (value > 0) {
            return 1;
        }
        if (value < 0) {
            return -1;
        }
        return 0;
    }
};

