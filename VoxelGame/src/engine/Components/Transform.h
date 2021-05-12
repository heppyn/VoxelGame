#pragma once

#include "Component.h"
#include "glm/vec3.hpp"

namespace Components {
class Transform : public Component {
  public:
    glm::vec3 Position{ 0 };
    glm::vec3 Rotation{ 0 };
    glm::vec3 Scale{ 1 };

    Transform() = default;
    Transform(glm::vec3 pos) : Position(pos) {}
    ~Transform() override = default;
    Transform(const Transform&) = default;
    Transform& operator=(const Transform&) = default;
    Transform(Transform&&) = default;
    Transform& operator=(Transform&&) = default;
};
} // namespace Components
