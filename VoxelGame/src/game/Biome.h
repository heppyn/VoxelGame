#pragma once
#include <vector>

#include "glm/vec2.hpp"
#include "Weather.h"

namespace Terrain {
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
};

class Biome {
  public:
    static float GetFreq(BiomeType type);
    static float GetHeightVar(BiomeType type);
    static BiomeType GetBiome(const glm::vec2& pos, Weather::Humidity humidity, Weather::Temperature temperature);
    
    static void Init();
    static void Clear();

  private:
    static float Frequency_;
    static std::vector<std::vector<std::vector<BiomeType>>> BiomeTable_;

    static void InitBiomeTable();
};
} // namespace Terrain
