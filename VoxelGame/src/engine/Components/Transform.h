#pragma once

#include "Component.h"
#include "engine/GameObject.h"
#include "glm/vec3.hpp"
#include "glm/gtx/transform.hpp"

namespace Components {
/**
 * \brief Holds object's transformations
 */
class Transform : public Component {
  public:
    // center of the object
    glm::vec3 Position{ 0 };
    glm::vec3 Rotation{ 0 };
    glm::vec3 Scale{ 1 };

    Transform() = default;
    Transform(glm::vec3 pos)
      : Position(pos) {}
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

    [[nodiscard]] bool IsOtherInside(const Transform& other) const {
        // assumes uniform scaling
        // TODO: change scale to float
        const auto maxDiff = std::abs(Scale.x - other.Scale.x) / 2.0f;
        return std::abs(Position.x - other.Position.x) <= maxDiff
               && std::abs(Position.y - other.Position.y) <= maxDiff
               && std::abs(Position.z - other.Position.z) <= maxDiff;
    }

    [[nodiscard]] bool IsOtherInside(const GameObject& go) const {
        assert(go.HasComponent<Transform>());
        return IsOtherInside(go.GetComponent<Transform>());
    }
};
} // namespace Components
