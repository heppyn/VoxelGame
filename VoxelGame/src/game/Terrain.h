#pragma once
#include "glm/vec2.hpp"

namespace Terrain {
enum class BlockType {
    Water,
    Stone,
    Sand,
    Dirt,
    Grass,
    OakLog,
    OakLeaf,
};

glm::vec2 GetTextPos(BlockType blockType);
}
