#pragma once
#include "glm/vec3.hpp"


namespace LSystems {
// turtle has a position and orientation
// http://algorithmicbotany.org/papers/abop/abop-ch1.pdf
// Chapter 1.5 modeling in three dimensions
class Turtle {
  public:
    explicit Turtle(const glm::vec3& position);

    void Rotate(float yaw, float pitch);
    void Move(const glm::vec3& dv);
    void MoveForward(float dz);
    void MoveSide(float dx);
    void MoveUp(float dy);
    [[nodiscard]] const glm::vec3& Position() const { return Position_; }

  private:
    static constexpr glm::vec3 WORLD_UP{ 0.0f, 1.0f, 0.0f };

    // turtle Attributes
    glm::vec3 Position_{ 0.0f };
    glm::vec3 Front_;
    glm::vec3 Up_;
    glm::vec3 Right_;
    // euler Angles
    float Yaw{ -90.0f }; // look to negative Z
    float Pitch{ 0.0f };

    void UpdateTurtleVectors();
};
} // namespace LSystems
