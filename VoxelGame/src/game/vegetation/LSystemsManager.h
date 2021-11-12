#pragma once
#include <vector>

#include "game/Terrain.h"
#include "glm/fwd.hpp"

namespace Terrain::Vegetation {
class LSystemsManager {
  public:
    // generate model matrices
    static void Init();
    // delete model matrices
    static void Clear();

    // Generate shrub based on preloaded assets
    [[nodiscard]] static std::vector<glm::mat4> GetShrub(const glm::vec3& pos, BlockType blockType);

  private:
    LSystemsManager() = default; // LSystemsManager is singleton

    static std::vector<std::vector<glm::mat4>> Shrubs_;

    static constexpr int SHRUB_COUNT{ 4 };

    inline static const auto SHRUB_PATH{ "./res/l-systems/plants/Shrubs.txt" };
};
} // namespace Terrain::Vegetation
