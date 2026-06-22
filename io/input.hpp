#pragma once
#include <variant>
#include "../datastructures/vector3.hpp"
#include <vector>


namespace io {
    enum EventType {
        KEYBOARD,
        MOUSE,
        MOUSE_POSITION,
        SPECIAL
    }

    struct MouseButtons {
        bool left;
		bool right;
		bool middle;
		bool extra1;
		bool extra2;
    };

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
        void read(std::vector<std::variant<KeyboardEvent, MouseButtons, Point2, SpecialKey>>& buffer) const;
        ~InputListener();
    };
}
