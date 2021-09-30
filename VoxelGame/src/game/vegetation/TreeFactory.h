#pragma once
#include <vector>

#include "engine/GameObject.h"
#include "game/Biome.h"


namespace Terrain::Vegetation {
class TreeFactory {
  public:
    static bool HasTree(const glm::vec3& pos, BiomeType biome);
    static std::vector<GameObject> GenerateTree(const glm::vec3& pos, BiomeType biome);

  private:
    constexpr static int DENSITY_DENSE{ 1 };
    constexpr static int DENSITY_NORMAL{ 1 };
    constexpr static int DENSITY_SPARSE{ 1 };

    constexpr static float FREQ_DENSE{ 2.5f };
    constexpr static float FREQ_NORMAL{ 2.5f };
    constexpr static float FREQ_SPARSE{ 2.5f };
};
} // namespace Terrain::Vegetation
