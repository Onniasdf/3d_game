#ifndef INPUT_HPP
#define INPUT_HPP
#include <variant>
#include <cstdint>


namespace game {
    struct Point {
        uint32_t x, y;
    };
    class InputListener {
        #ifdef __linux__
        int inputEpoll;
        #elif _WIN32
        #include <windows.h>
        HANDLE input;
        #endif

        std::variant<Point, char> read();
    };
}

#endif
