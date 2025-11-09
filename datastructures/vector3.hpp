#ifndef INC_3D_GAME_VECTOR3_HPP
#define INC_3D_GAME_VECTOR3_HPP

#include <cmath>

struct Vector3 {
    double x = 0, y = 0, z = 0;

    Vector3(const double x, const double y, const double z) : x(x), y(y), z(z) {}
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


#endif
