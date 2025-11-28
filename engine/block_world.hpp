#pragma once
#include <cstdint>
#include <optional>

#include "../datastructures/vector3.hpp"
#include <memory>

namespace engine {
    struct Cube {
		size_t x, y, z;
    };

    class LimitedBlockWorld {
        std::unique_ptr<int16_t[]> blocks;
        Cube quadrantSize;
        Cube mapSize;

        [[nodiscard]] int16_t* getBlock(const Vector3& pos) const {
            return &blocks[(static_cast<intptr_t>(pos.z) + quadrantSize.z) * mapSize.y * mapSize.x + (static_cast<intptr_t>(pos.y) + quadrantSize.y) * mapSize.x + static_cast<intptr_t>(pos.x) + quadrantSize.x];
        }

        [[nodiscard]] bool isInBounds(Vector3 pos) const {
            const Vector3 absPos = pos.abs();
            return absPos.x < quadrantSize.x && absPos.y < quadrantSize.y && absPos.z < quadrantSize.z;
        }
    public:
        LimitedBlockWorld(size_t x, size_t y, size_t z) : quadrantSize({ x, y, z }), mapSize(x * 2, y * 2, z * 2) {
            size_t size = mapSize.z * mapSize.y * mapSize.x;
            blocks = std::make_unique<int16_t[]>(size);
            for (size_t i = 0; i < size; i++) {
                blocks[i] = -1;
            }
        }
        std::optional<uint16_t> get(const Vector3& pos) const {
            if (!isInBounds(pos)) {
                return {0};
            }
            int16_t block = *getBlock(pos);
            if (block == -1) return {};
            return { block };
        }

        void set(const Vector3& pos, const std::optional<uint16_t> value) const {
            if (!isInBounds(pos)) return;
            int16_t* block = getBlock(pos);
            if (value.has_value()) {
                *block = value.value();
            } else {
                *block = -1;
            }
        }
    };
}
