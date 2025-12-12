#pragma once

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <algorithm>

struct Vector2 {
    double x = 0, y = 0;

    // Constructors
    Vector2() = default;
    Vector2(double x, double y) : x(x), y(y) {}

    // Arithmetic operators
    Vector2 operator+(const Vector2& other) const {
        return { x + other.x, y + other.y };
    }
    Vector2 operator-(const Vector2& other) const {
        return { x - other.x, y - other.y };
    }
    Vector2 operator-() const {
        return { -x, -y };
    }

    Vector2 operator*(double scalar) const {
        return { x * scalar, y * scalar };
    }
    Vector2 operator*(const Vector2& other) const {
        return { x * other.x, y * other.y };
    }
    Vector2 operator/(double scalar) const {
        return { x / scalar, y / scalar };
    }
    Vector2 operator/(const Vector2& other) const {
        return { x / other.x, y / other.y };
    }

    // Compound assignment operators
    void operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
    }
    void operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
    }
    void operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
    }
    void operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
    }

    // Math helpers
    [[nodiscard]] double length() const {
        return std::sqrt(x * x + y * y);
    }

    [[nodiscard]] Vector2 floor() const {
        return { std::floor(x), std::floor(y) };
    }
    [[nodiscard]] Vector2 ceil() const {
        return { std::ceil(x), std::ceil(y) };
    }
    [[nodiscard]] Vector2 round() const {
        return { std::round(x), std::round(y) };
    }
    [[nodiscard]] Vector2 abs() const {
        return { std::abs(x), std::abs(y) };
    }
    [[nodiscard]] Vector2 sign() const {
        return { getSign(x), getSign(y) };
    }

    // Modifiers
    [[nodiscard]] Vector2 withX(double newX) const {
        return { newX, y };
    }
    [[nodiscard]] Vector2 withY(double newY) const {
        return { x, newY };
    }

private:
    static double getSign(double value) {
        if (value > 0) return 1;
        if (value < 0) return -1;
        return 0;
    }
};
struct Vector3 {
    double x = 0, y = 0, z = 0;

    Vector3(const double x, const double y, const double z) : x(x), y(y), z(z) {}
	Vector3(const Vector2& vec2) : x(vec2.x), y(vec2.y), z(0) {}
    Vector3() = default;
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

    Vector3 clamp(double min, double max) const {
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

struct Point {
    uint32_t x, y;

     Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }

    Point operator-(const Point& other) const {
         return {x - other.x, y - other.y};
     }
};
