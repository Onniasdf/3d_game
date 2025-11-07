#ifndef INC_3D_GAME_WORLD_HPP
#define INC_3D_GAME_WORLD_HPP
#include "../datastructures/Vector3.hpp"
#include <concepts>
#include <cstdint>

namespace engine {

    template <typename T>
    concept Interactable = requires(T t, Vector3& position, uint64_t id, std::optional<uint64_t> setId)
    {
        { t.set(position, setId) };
        { t.get(position) } -> std::same_as<std::optional<uint64_t>>;
    };

    template <Interactable T>
    Vector3 castRay(T& world, Vector3& start, Vector3& step) {
        Vector3 position = start;
        do {
            position += step;
        } while (!world.get(position).has_value());
        return position;
    }
}

#endif
