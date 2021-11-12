#pragma once

#include "Component.h"
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
#include "glm/gtx/transform.hpp"

namespace Components {
class Transform : public Component {
  public:
    // center of the object
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

    [[nodiscard]] glm::mat4 ModelMat() const {
        auto model = glm::mat4(1.0f); // identity matrix
        model = glm::translate(model, Position);
        return glm::scale(model, Scale);
    }
};
} // namespace Components
