#ifndef RENDERING_HPP
#define RENDERING_HPP

#include <sstream>
#include <iostream>
#include "../datastructures/rgb_colour.hpp"

namespace game {
    class Renderer {
        std::ostringstream buffer{};
        uint32_t currentColour = 0;

    public:

        Renderer() = default;

        void write(const RgbColour colour) {
            const uint32_t code = colour.toAnsiCode();
            if (currentColour == code) {
                buffer << "#";
                return;
            }
            currentColour = code;
            buffer << "\033[38;5;" << code << "m@";
        }

        void writeLine() {
            buffer << "\n";
        }

        void startFrame() {
            buffer << "\033[H";
        }

        void flush() {
            std::cout << buffer.str();
            buffer.clear();
        }
    };
}

#endif
