#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "engine/Chunk.h"
#include "Terrain.h"

namespace Terrain {
class TerrainGen {
  public:
    static ::Chunk GenerateChunk(const glm::vec2& position);

  private:
    static void PlaceBlock(std::vector<GameObject>& buffer, const glm::vec2& pos);
    static void PlaceVegetation(std::vector<GameObject>& buffer, const glm::vec2& pos);
    static float LowestNeigh(const glm::vec2& pos);
    static float LowestNeighSmooth(const glm::vec2& pos);
    static float HightestNeigh(const glm::vec2& pos);
    static float BlockHeight(const glm::vec2& pos);
    static float BlockHeightSmooth(const glm::vec2& pos);
    static BlockType GetBlockType(const glm::vec3& pos, float surfHeight);
    static std::vector<float> NeighHeights(const glm::vec2& pos);
    static std::vector<float> NeighHeightsSmooth(const glm::vec2& pos);
};
} // namespace Terrain
