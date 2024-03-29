#pragma once
#include <vector>

#include <engine/GameObject.h>

#include "Biome.h"


namespace Terrain::Vegetation {
/**
 * \brief Factory for tree generation.
 * Chooses which tree to generate based on biome.
 * Specify tree densities.
 */
class TreeFactory {
  public:
    [[nodiscard]] static bool HasTree(const glm::vec3& pos, BiomeType biome);
    [[nodiscard]] static std::vector<glm::mat4> GenerateTree(const glm::vec3& pos, BiomeType biome);

  private:
    constexpr static int DENSITY_DENSE{ 1 };
    constexpr static int DENSITY_NORMAL{ 1 };
    constexpr static int DENSITY_SPARSE{ 1 };

    constexpr static float FREQ_DENSE{ 1.5f };
    constexpr static float FREQ_NORMAL{ 2.5f };
    constexpr static float FREQ_SPARSE{ 6.5f };
    constexpr static float FREQ_RARE{ 7.5f };

    [[nodiscard]] static bool HasNeighTree(const glm::vec3& pos, BiomeType biome, int regionSize);
    [[nodiscard]] static bool CanHaveTree(const glm::vec3& pos, BiomeType biome);
};
} // namespace Terrain::Vegetation
