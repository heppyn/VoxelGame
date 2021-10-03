#pragma once

#include "Terrain.h"
#include "engine/GameObject.h"


namespace Terrain {
class BlockFactory {
  public:
    [[nodiscard]] static GameObject CreateBlock(const glm::vec3& pos, BlockType blockType);
};
} // namespace Terrain
