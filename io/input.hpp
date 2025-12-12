#pragma once
#include <optional>
#include <variant>
#include "../datastructures/vector3.hpp"
#include <vector>
#include <cstdint>


namespace io {
    enum MouseButtons : uint8_t {
        LEFT,
        RIGHT = 1 << 1,
        MIDDLE = 1 << 2,
        EXTRA1 = 1 << 3,
        EXTRA2 = 1 << 4,
    };

    inline MouseButtons operator|(MouseButtons a, MouseButtons b) {
        return static_cast<MouseButtons>(
            static_cast<int>(a) | static_cast<int>(b)
        );
    }

    inline MouseButtons operator&(MouseButtons a, MouseButtons b) {
        return static_cast<MouseButtons>(
            static_cast<int>(a) & static_cast<int>(b)
        );
    }
    inline MouseButtons& operator|=(MouseButtons& a, MouseButtons b) {
        a = a | b;
        return a;
    }

    inline bool hasFlag(const MouseButtons flags, const MouseButtons flag) {
        return static_cast<uint8_t>(flags & flag) != 0;
    }

    struct KeyboardEvent {
        char key;
        bool down;
    };

    enum SpecialKey {
        ESCAPE
    };

    class InputListener {
        #ifdef __linux__
        int mouseInput;
        int keyboardInput;
        #elif _WIN32
        void* handle;
        explicit InputListener(void* handle) : handle(handle) {}
        #endif
    public:
        static InputListener create();
        void read(std::vector<std::variant<KeyboardEvent, MouseButtons, Point, SpecialKey>>& buffer) const;
        ~InputListener();
    };
}
