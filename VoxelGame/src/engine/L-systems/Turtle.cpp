#include "Turtle.h"

#include <glm/glm.hpp>


LSystems::Turtle::Turtle(const glm::vec3& position)
  : Position_(position), Front_(0.0f), Up_(0.0f), Right_(0.0f) {
    UpdateTurtleVectors();
}

void LSystems::Turtle::Rotate(float yaw, float pitch) {
    Yaw += yaw;
    // stuff break when pitch is 90 deg
    Pitch = glm::clamp(Pitch + pitch, -89.99f, 89.99f);
    UpdateTurtleVectors();
}

void LSystems::Turtle::Move(const glm::vec3& dv) {
    Position_ += dv;
}

void LSystems::Turtle::MoveForward(float dz) {
    Position_ += Front_ * dz;
}
void LSystems::Turtle::MoveSide(float dx) {
    Position_ += Right_ * dx;
}

void LSystems::Turtle::MoveUp(float dy) {
    Position_ += Up_ * dy;
}

void LSystems::Turtle::UpdateTurtleVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front_ = glm::normalize(front);
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement
    Right_ = glm::normalize(glm::cross(Front_, WORLD_UP));
    Up_ = glm::normalize(glm::cross(Right_, Front_));
}
