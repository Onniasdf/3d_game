#ifndef INPUT_HPP
#define INPUT_HPP
#include <optional>
#include <variant>
#include "../datastructures/vector3.hpp"
#include <vector>


namespace game {
    enum MouseButtons {
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

    inline MouseButtons operator^(MouseButtons a, MouseButtons b) {
        return static_cast<MouseButtons>(
            static_cast<int>(a) ^ static_cast<int>(b)
        );
    }

    inline MouseButtons operator~(MouseButtons a) {
        return static_cast<MouseButtons>(
            ~static_cast<int>(a)
        );
    }

    inline MouseButtons& operator|=(MouseButtons& a, MouseButtons b) {
        a = a | b;
        return a;
    }

    inline MouseButtons& operator&=(MouseButtons& a, MouseButtons b) {
        a = a & b;
        return a;
    }

    inline MouseButtons& operator^=(MouseButtons& a, MouseButtons b) {
        a = a ^ b;
        return a;
    }

    inline bool hasFlag(MouseButtons flags, MouseButtons flag) {
        return static_cast<int>(flags & flag) != 0;
    }

    struct MouseEvent {
        MouseButtons buttons;
        Point position;

        MouseEvent(MouseButtons buttons, Point p) : buttons(buttons), position(p) {}
    };

    struct KeyboardEvent {
        char key;
        bool down;
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
        void read(std::vector<std::variant<KeyboardEvent, MouseEvent>>& buffer) const;
    };
}

#endif
