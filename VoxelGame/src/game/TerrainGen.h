#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "engine/Chunk.h"
#include "Terrain.h"
#include "Biome.h"
#include "vegetation/GrassFactory.h"


namespace Terrain {
class TerrainGen {
  public:
    static ::Chunk GenerateChunk(const glm::vec2& position);
    inline static constexpr float MAX_BLOCK_HEIGHT{ 255.0f };

  private:
    // TODO: are all functions const?
    static Vegetation::GrassFactory GrassFactory_;

    static BiomeType PlaceBlock(Chunk& chunk, const glm::vec2& pos);
    static void PlaceVegetation(Chunk& chunk, const glm::vec2& pos, BiomeType biome);
    static void SetBlockInfo(Chunk& chunk, const glm::vec2& pos, Weather::Humidity humidity, Weather::Temperature temperature, BiomeType biome, int height);
    static float LowestNeigh(const glm::vec2& pos);
    static BlockType GetBlockType(const glm::vec3& pos, float surfHeight, BiomeType biome);
    static std::vector<float> NeighHeights(const glm::vec2& pos);
    static Weather::Humidity GetHumidity(const glm::vec2& pos);
    static Weather::Temperature GetTemperature(const glm::vec3& pos);
};
} // namespace Terrain
