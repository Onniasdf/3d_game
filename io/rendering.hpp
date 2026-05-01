#pragma once

#include <sstream>
#include <iostream>
#include "../datastructures/rgb_colour.hpp"
#include <cstdint>
#include "output.hpp"
#include <string>

namespace io {
    class Renderer {
        std::ostringstream buffer{};
        uint32_t currentColour = 0;

        const std::string CLEAR_SCREEN = "\033[H\033[J";
        const std::string RESET_COLOUR = "\033[0m";
        const std::string START_COLOUR = "\033[38;5;";
        const std::string END_COLOUR = "m@";

    public:

        Renderer() = default;

        void write(const RgbColour colour) {
            const uint32_t code = colour.toAnsiCode();
            if (currentColour == code) {
                buffer << "@";
                return;
            }
            currentColour = code;
            buffer << START_COLOUR << code << END_COLOUR;
        }

        void writeLine() {
            buffer << std::endl;
        }

        void startFrame() {
            buffer << CLEAR_SCREEN;
        }

        void flush() {
            buffer << RESET_COLOUR;
            currentColour = 0;
			const std::string& str = buffer.str();
			write_to_output(reinterpret_cast<const uint8_t*>(str.c_str()), str.size());
            buffer.str("");
			buffer.clear();
        }
    };
}

