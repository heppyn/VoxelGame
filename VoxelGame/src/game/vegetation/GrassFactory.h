#pragma once
#include "engine/GameObject.h"
#include "game/Biome.h"
#include "game/BlockFactory.h"


namespace Terrain::Vegetation {
enum class GrassDensity {
    Dense,
    Normal,
    Sparse,
    None,
};

class GrassFactory {
  public:
    [[nodiscard]] static std::vector<GameObject> GenerateGrass(const glm::vec3& pos, BiomeType biome);
    [[nodiscard]] static bool HasGrass(const glm::vec3& pos, BiomeType biome);

  private:
    static BlockFactory BlockFactory_;

    [[nodiscard]] static GrassDensity GetGrassDensity(BiomeType biome);
};
} // namespace Terrain::Vegetation
