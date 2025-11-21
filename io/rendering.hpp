#ifndef RENDERING_HPP
#define RENDERING_HPP

#include <sstream>
#include <iostream>
#include "../datastructures/rgb_colour.hpp"
#include <cstdint>

namespace io {
    class Renderer {
        std::ostringstream buffer{};
        uint32_t currentColour = 0;

    public:

        Renderer() = default;

        void write(const RgbColour colour) {
            const uint32_t code = colour.toAnsiCode();
            if (currentColour == code) {
                buffer << "@";
                return;
            }
            currentColour = code;
            buffer << "\033[38;5;" << code << "m@";
        }

        void writeLine() {
            buffer << std::endl;
        }

        void startFrame() {
            buffer << "\033[H\033[J";
        }

        void flush() {
            buffer << "\033[0m";
            currentColour = 0;
            std::cout << buffer.str() << std::flush;
            buffer.str("");
			buffer.clear();
        }
    };
}

#endif
