#pragma once

#include "engine/Chunk.h"
#include "glm/vec2.hpp"

namespace Terrain {
class TerrainGen {
  public:
    static ::Chunk GenerateChunk(const glm::vec2& position);

  private:
    static void PlaceBlock(std::vector<GameObject>& buffer, const glm::vec2& pos);
    static float LowestNeigh(const glm::vec2& pos);
    static float BlockHeight(const glm::vec2& pos);
};
} // namespace Terrain
