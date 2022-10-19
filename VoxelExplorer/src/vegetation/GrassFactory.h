#pragma once
#include <engine/GameObject.h>
#include <engine/L-systems/LSystemExecutor.h>
#include <engine/BlockFaces.h>

#include "Biome.h"
#include "BlockFactory.h"


namespace Terrain::Vegetation {
enum class GrassDensity {
    Dense,
    Normal,
    Sparse,
    None,
};

/**
 * \brief Factory for creating grass
 */
class GrassFactory {
  public:
    explicit GrassFactory(std::string_view grassFile);

    [[nodiscard]] static std::vector<GameObject> GenerateGrass(const glm::vec3& pos, BiomeType biome);
    [[nodiscard]] std::vector<GameObject> GenerateLSystemGrass(const glm::vec3& pos, BiomeType biome);
    [[nodiscard]] static bool HasGrass(const glm::vec3& pos, BiomeType biome);
    [[nodiscard]] static const Engine::Cube::BlockFaces& GrassCube() { return Engine::Cube::PIPE; }

  private:
    static BlockFactory BlockFactory_;
    std::vector<LSystems::LSystem> LSystems_;
    LSystems::LSystemExecutor LExecutor_{ 2 };

    [[nodiscard]] static GrassDensity GetGrassDensity(BiomeType biome);
};
} // namespace Terrain::Vegetation
