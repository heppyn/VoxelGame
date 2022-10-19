#pragma once
#include <vector>

#include <glm/vec2.hpp>

#include "Weather.h"


namespace Terrain {
/**
 * \brief All supported biomes
 */
enum class BiomeType {
    Ice,
    Tundra,
    Grassland,
    ColdDesert,
    Woodland,
    BorealForest,
    Shrubland,
    SeasonalForest,
    TemperateRainforest,
    SubtropicalDesert,
    TropicalForest,
    Savanna,
    TropicalRainforest,
    // not included in the biome table
    Water,
};

/**
 * \brief Chooses biome based on humidity and temperature
 */
class Biome {
  public:
    static BiomeType GetBiome(const glm::vec2& pos, Weather::Humidity humidity, Weather::Temperature temperature);

    static void Init();
    static void Clear();

  private:
    static float Frequency_;
    static std::vector<std::vector<std::vector<BiomeType>>> BiomeTable_;

    static void InitBiomeTable();
};
} // namespace Terrain
