#ifndef INC_3D_GAME_RGBCOLOUR_HPP
#define INC_3D_GAME_RGBCOLOUR_HPP
#include <cstdint>

struct RgbColour {
    uint8_t red = 0, green = 0, blue = 0;


    static constexpr uint32_t toAnsiIndex(const uint32_t value) {
        return value * 5 / 255;
    }

    [[nodiscard]] uint32_t toAnsiCode() const {
        const uint32_t ri = toAnsiIndex(red);
        const uint32_t gi = toAnsiIndex(green);
        const uint32_t bi = toAnsiIndex(blue);
        return 16 + 36 * ri + 6 * gi + bi;
    }
};



#endif
