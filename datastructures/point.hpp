#pragma once
#include <cstdint>


struct Point2 {
    uint32_t x{}, y{};

    Point2 operator+(const Point2& other) const {
        return {x + other.x, y + other.y};
    }

    Point2 operator-(const Point2& other) const {
        return {x - other.x, y - other.y};
    }
};

enum Sign : int8_t {
    Undefined = 0,
    Positive = 1,
    Negative = -1,
};

struct Sign3 {
    Sign x{}, y{}, z{};
};