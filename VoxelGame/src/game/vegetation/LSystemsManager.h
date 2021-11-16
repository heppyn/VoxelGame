#pragma once
#include <vector>

#include "game/Terrain.h"
#include "glm/fwd.hpp"

namespace Terrain::Vegetation {
namespace Detail {
    struct PlantModel {
        // represents plant which can have multiple distinct block variations
        // eq. stem and leaves
        std::vector<std::vector<glm::mat4>> Model;

        [[nodiscard]] size_t Size() const;
    };
}
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

    static std::vector<Detail::PlantModel> Shrubs_;

    static constexpr int SHRUB_COUNT{ 8 };

    inline static const auto SHRUB_PATH{ "./res/l-systems/plants/Shrubs.txt" };
};
} // namespace Terrain::Vegetation
