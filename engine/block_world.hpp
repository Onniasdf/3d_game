#ifndef INC_3D_GAME_BLOCK_WORLD_HPP
#define INC_3D_GAME_BLOCK_WORLD_HPP
#include <cstdint>
#include <optional>

#include "../datastructures/Vector3.hpp"

namespace engine {
    class LimitedBlockWorld {
        int16_t* blocks;
        size_t x, y, z;

        LimitedBlockWorld(size_t x, size_t y, size_t z) : blocks(new int16_t[z * 2 * y * 2 * x * 2]), x(x), y(y), z(z) {}

        [[nodiscard]] int16_t* getBlock(const Vector3& pos) const {
            return &blocks[(static_cast<size_t>(pos.z) + z) * z + (static_cast<size_t>(pos.y) + y) * y + (static_cast<size_t>(pos.x) + x) * x];
        }

        [[nodiscard]] bool validate(Vector3 pos) const {
            const Vector3 absPos = pos.abs();
            return absPos.x >= x || absPos.y >= y || absPos.z >= z;
        }
    public:
        std::optional<uint16_t> get(const Vector3& pos) {
            if (!validate(pos)) {
                return {0};
            }
            int16_t block = *getBlock(pos);
            if (block == -1) return {};
            return { block };
        }

        void set(const Vector3& pos, const std::optional<uint16_t> value) const {
            if (!validate(pos)) return;
            int16_t* block = getBlock(pos);
            if (value.has_value()) {
                *block = value.value();
            } else {
                *block = -1;
            }
        }
    };
}

#endif
