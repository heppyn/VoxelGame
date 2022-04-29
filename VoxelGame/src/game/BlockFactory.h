#pragma once

#include "Terrain.h"
#include "engine/GameObjectFactory.h"
#include "engine/GameObject.h"


namespace Terrain {
/**
 * \brief Enhances GameObjectFactory with specific block types instead of texture positions
 */
class BlockFactory {
  public:
    BlockFactory() = default;
    BlockFactory(const glm::vec3& scale, const glm::vec3& positionOffset);

    [[nodiscard]] static GameObject CreateBlock(const glm::vec3& pos, BlockType blockType);
    [[nodiscard]] GameObject CreateFromPreset(const glm::vec3& pos, BlockType blockType) const;
    [[nodiscard]] GameObject CreateFromPreset(const glm::vec3& pos, BlockType blockType);
    [[nodiscard]] GameObject CreateStacked(const glm::vec3& pos, BlockType blockType);

    BlockFactory& Scale(const glm::vec3& scale);
    BlockFactory& PositionOffset(const glm::vec3& positionOffset);

  private:
    GameObjectFactory GOFactory_{ glm::vec3(1.0f), glm::vec3(0.0f) };
};
} // namespace Terrain
