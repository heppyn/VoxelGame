#pragma once
#include "glm/vec2.hpp"

namespace Terrain {
enum class BiomeType {
    Plains,
    Forrest,
    Hills,
    Desert,
};

class Biome {
  public:
    static float GetFreq(BiomeType type);
    static float GetHeightVar(BiomeType type);
    static BiomeType GetBiome(const glm::vec2& pos);

private:
    static float Frequency_;
};

} // namespace Terrain
