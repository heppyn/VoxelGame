#pragma once
#include <vector>

#include "glm/fwd.hpp"
#include "engine/GameObject.h"
#include "game/Terrain.h"
#include "engine/L-systems/LSystem.h"

namespace Terrain::Vegetation {
namespace Detail {
    // represents plant which can have multiple distinct block variations
    // eq. stem and leaves
    class PlantModel {
      public:
        std::vector<std::vector<glm::mat4>> Model;

        explicit PlantModel(const std::vector<std::vector<GameObject>>& gameObjects);

        [[nodiscard]] size_t Size() const;
    };
} // namespace Detail
class LSystemsManager {
  public:
    // generate model matrices
    static void Init();
    // delete model matrices
    static void Clear();

    // Generate shrub based on preloaded assets
    [[nodiscard]] static std::vector<glm::mat4> GetShrub(const glm::vec3& pos, BlockType blockType);
    [[nodiscard]] static std::vector<glm::mat4> GetShrub(const glm::vec3& pos, const std::vector<BlockType>& blockTypes);

    [[nodiscard]] static std::vector<glm::mat4> GetAcacia(const glm::vec3& pos, BlockType trunk, BlockType leaves);

  private:
    LSystemsManager() = default; // LSystemsManager is singleton

    static std::vector<Detail::PlantModel> Shrubs_;
    static std::vector<LSystems::LSystem> AcaciaLSystems_;

    static constexpr int SHRUB_COUNT{ 8 };

    inline static const auto SHRUB_PATH{ "./res/l-systems/plants/Shrubs.txt" };
    inline static const auto ACACIA_PATH{ "./res/l-systems/plants/Acacia.txt" };

    [[nodiscard]] static std::vector<glm::mat4> GetPlant(const glm::vec3& pos, const Detail::PlantModel& plantModel, const std::vector<BlockType>& blockTypes);
    [[nodiscard]] static std::vector<glm::mat4> GetPlant(const Detail::PlantModel& plantModel, const std::vector<BlockType>& blockTypes);
};
} // namespace Terrain::Vegetation
