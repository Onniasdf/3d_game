cmake_minimum_required(VERSION 4.0)
project(3d_game)

set(CMAKE_CXX_STANDARD 23)

add_executable(3d_game main.cpp
        engine/entity.hpp
        datastructures/Vector3.hpp
        engine/world.hpp
        datastructures/rgb_colour.hpp
        engine/block_world.hpp
        engine/engine.hpp
        engine/engine.cpp
        engine/interface.hpp
)
