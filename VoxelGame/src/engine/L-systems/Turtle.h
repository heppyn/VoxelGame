#pragma once
#include "glm/vec3.hpp"


namespace LSystems::Detail {
// turtle has a position and orientation
// http://algorithmicbotany.org/papers/abop/abop-ch1.pdf
// Chapter 1.5 modeling in three dimensions
class Turtle {
  public:
    explicit Turtle(const glm::vec3& position);
    Turtle(const glm::vec3& position, float scale);

    void Rotate(float yaw, float pitch);
    void Move(const glm::vec3& dv);
    void MoveForward(float dz);
    void MoveBackward(float dz) { MoveForward(-dz); }
    void MoveSide(float dx);
    void MoveUp(float dy);
    void MoveDown(float dy) { MoveUp(-dy); }

    void MoveForward() { MoveForward(Scale_); }
    void MoveBackward() { MoveForward(-Scale_); }
    void MoveSide() { MoveSide(Scale_); }
    void MoveUp() { MoveUp(Scale_); }
    void MoveDown() { MoveUp(-Scale_); }

    [[nodiscard]] const glm::vec3& Position() const { return Position_; }
    [[nodiscard]] float Scale() const { return Scale_; }
    void Scale(float scale) { Scale_ = scale; }
    [[nodiscard]] uint8_t OutputBuffer() const { return OutputBuffer_; }
    void OutputBuffer(uint8_t buffer) { OutputBuffer_ = buffer; }

  private:
    static constexpr glm::vec3 WORLD_UP{ 0.0f, 1.0f, 0.0f };

    // turtle Attributes
    glm::vec3 Position_{ 0.0f };
    glm::vec3 Front_;
    glm::vec3 Up_;
    glm::vec3 Right_;
    // euler Angles
    float Yaw_{ -90.0f }; // look to negative Z
    float Pitch_{ 0.0f };
    float Scale_{ 1.0f };
    uint8_t OutputBuffer_{ 0 };

    void UpdateTurtleVectors();
};
} // namespace LSystems::Detail
