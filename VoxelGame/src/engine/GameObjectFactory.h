#pragma once
#include "GameObject.h"
#include "glm/vec3.hpp"

class GameObjectFactory {
  public:
    GameObjectFactory() = default;
    GameObjectFactory(const glm::vec3& scale, const glm::vec3& positionOffset);

    [[nodiscard]] static GameObject CreateObject(const glm::vec3& pos, const glm::vec2& tex);
    [[nodiscard]] GameObject CreateFromPreset(const glm::vec3& pos, const glm::vec2& tex) const;
    [[nodiscard]] GameObject CreateFromPreset(const glm::vec3& pos, const glm::vec2& tex);
    [[nodiscard]] GameObject CreateStacked(const glm::vec3& pos, const glm::vec2& tex);

    GameObjectFactory& Scale(const glm::vec3& scale);
    GameObjectFactory& PositionOffset(const glm::vec3& positionOffset);

  private:
    glm::vec3 Scale_{ 1.0f };
    glm::vec3 PositionOffset_{ 0.0f };
    glm::vec3 OrigPosOffset_{ 0.0f };
};
