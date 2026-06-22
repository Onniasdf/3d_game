cmake_minimum_required(VERSION 4.0)
project(3d_game)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(3d_game
        main.cpp
        engine/engine.cpp
        engine/entity.cpp
        engine/interface.cpp
        engine/raytracing.cpp
        io/input_windows.cpp
        io/io_handling.cpp
        io/output_windows.cpp
        game/player.cpp
        game/textures.cpp
        datastructures/point.hpp)
