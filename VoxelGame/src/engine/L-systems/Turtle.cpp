#include "Turtle.h"

#include <glm/glm.hpp>

#include "helpers/Math.h"


LSystems::Detail::Turtle::Turtle(const glm::vec3& position)
  : Position_(position), Front_(0.0f), Up_(0.0f), Right_(0.0f) {
    UpdateTurtleVectors();
}

LSystems::Detail::Turtle::Turtle(const glm::vec3& position, float scale)
  : Position_(position), Front_(0.0f), Up_(0.0f), Right_(0.0f), Scale_(scale) {
    UpdateTurtleVectors();
}

void LSystems::Detail::Turtle::Rotate(float yaw, float pitch) {
    Yaw_ += yaw;
    Pitch_ += pitch;
    // stuff breaks when pitch is 90 deg
    if (Helpers::Math::Equal(cos(glm::radians(Pitch_)), 0.0f))
        Pitch_ -= 0.01f;
    UpdateTurtleVectors();
}

void LSystems::Detail::Turtle::Move(const glm::vec3& dv) {
    Position_ += dv;
}

void LSystems::Detail::Turtle::MoveForward(float dz) {
    Position_ += Front_ * dz;
}
void LSystems::Detail::Turtle::MoveSide(float dx) {
    Position_ += Right_ * dx;
}

void LSystems::Detail::Turtle::MoveUp(float dy) {
    Position_ += Up_ * dy;
}

void LSystems::Detail::Turtle::UpdateTurtleVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw_)) * cos(glm::radians(Pitch_));
    front.y = sin(glm::radians(Pitch_));
    front.z = sin(glm::radians(Yaw_)) * cos(glm::radians(Pitch_));
    Front_ = glm::normalize(front);
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement
    Right_ = glm::normalize(glm::cross(Front_, WORLD_UP));
    Up_ = glm::normalize(glm::cross(Right_, Front_));
}
