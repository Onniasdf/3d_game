cmake_minimum_required(VERSION 4.0)
project(3d_game)

set(CMAKE_CXX_STANDARD 23)

add_executable(3d_game main.cpp
        engine/physics.hpp
        datastructures/vector3.hpp
        datastructures/orientation.hpp
        datastructures/rgb_colour.hpp
        engine/block_world.hpp
        engine/engine.hpp
        engine/engine.cpp
        engine/interface.hpp
        io/io_handling.hpp
        io/input.hpp
        io/io_handling.cpp
        io/input_windows.cpp
        io/rendering.hpp
        engine/raytracing.cpp
        engine/raytracing.hpp
        engine/interface.cpp
        game/player.hpp
        game/player.cpp
        game/textures.cpp
        engine/entity.cpp
  "game/player.cpp" "io/output_windows.cpp" "game/textures.cpp"
        engine/entity.cpp)
