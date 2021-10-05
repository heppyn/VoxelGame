#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "engine/Chunk.h"
#include "Terrain.h"
#include "Biome.h"


namespace Terrain {
class TerrainGen {
  public:
    static ::Chunk GenerateChunk(const glm::vec2& position);
    inline static const float MAX_BLOCK_HEIGHT{ 255.0f };

  private:
    static BiomeType PlaceBlock(Chunk& chunk, const glm::vec2& pos);
    static void PlaceVegetation(Chunk& chunk, const glm::vec2& pos, BiomeType biome);
    static float LowestNeigh(const glm::vec2& pos);
    static float LowestNeighSmooth(const glm::vec2& pos);
    static float HightestNeigh(const glm::vec2& pos);
    static float BlockHeight(const glm::vec2& pos);
    static float BlockHeightSmooth(const glm::vec2& pos);
    static BlockType GetBlockType(const glm::vec3& pos, float surfHeight, BiomeType biome);
    static std::vector<float> NeighHeights(const glm::vec2& pos);
    static std::vector<float> NeighHeightsSmooth(const glm::vec2& pos);
    static Weather::Humidity GetHumidity(const glm::vec2& pos);
    static Weather::Temperature GetTemperature(const glm::vec3& pos);
};
} // namespace Terrain
