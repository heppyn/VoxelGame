#pragma once
#include "Component.h"
#include "engine/ResourceManager.h"
#include "glm/vec2.hpp"

namespace Components {
class SpritesheetTex : public Components::Component {
  private:
    glm::vec2 TexPos_;

  public:
    explicit SpritesheetTex(const glm::vec2& texPos) : TexPos_(0) {
        const auto& texSize = ResourceManager::GetSpriteSheetSize();
        TexPos_ = { texPos.x, texSize.y - 1 - texPos.y };
    }
    SpritesheetTex(const SpritesheetTex&) = default;
    SpritesheetTex& operator=(const SpritesheetTex&) = default;
    SpritesheetTex(SpritesheetTex&&) = default;
    SpritesheetTex& operator=(SpritesheetTex&&) = default;
    ~SpritesheetTex() override = default;

    [[nodiscard]] const glm::vec2& GetTexPos() const {
        return TexPos_;
    }
};
}; // namespace Components
