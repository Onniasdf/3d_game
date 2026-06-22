#pragma once

struct Vector2 {
    double x = 0, y = 0;

    enum Axis {
        X, Y
    };

    // Constructors
    Vector2() = default;
    Vector2(const double x, const double y) : x(x), y(y) {}

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

    Vector2 operator*(const double scalar) const {
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

