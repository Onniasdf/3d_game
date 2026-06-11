cmake_minimum_required(VERSION 4.0)
project(3d_game)

set(CMAKE_CXX_STANDARD 23)

add_executable(3d_game
        main.cpp
        datastructures/orientation.hpp
        datastructures/rgb_colour.hpp
        datastructures/vector2.hpp
        datastructures/vector3.hpp
        engine/block_world.hpp
        engine/engine.hpp
        engine/engine.cpp
        engine/entity.cpp
        engine/interface.hpp
        engine/interface.cpp
        engine/physics.hpp
        engine/raytracing.hpp
        engine/raytracing.cpp
        io/input.hpp
        io/input_windows.cpp
        io/io_handling.hpp
        io/io_handling.cpp
        io/output_windows.cpp
        io/rendering.hpp
        game/player.hpp
        game/player.cpp
        game/textures.cpp)

#target_link_options(3d_game PRIVATE
#        -static-libgcc
#        -static-libstdc++
#        -static)