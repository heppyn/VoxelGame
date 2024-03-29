#include "Camera.h"

#include <algorithm>

#include "helpers/Print.h"
#include "engine/Log.h"


Renderer::Camera::Camera(glm::vec3 position /*= glm::vec3(0.0f, 0.0f, 0.0f)*/, glm::vec3 up /*= glm::vec3(0.0f, 1.0f, 0.0f)*/, float yaw /*= YAW*/, float pitch /*= PITCH*/)
  : Position(position)
  , Front(glm::vec3(0.0f, 0.0f, -1.0f))
  , WorldUp(up)
  , Yaw(yaw)
  , Pitch(pitch) {
    UpdateCameraVectors();
}

Renderer::Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
  : Front(glm::vec3(0.0f, 0.0f, -1.0f)) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    UpdateCameraVectors();
}

glm::mat4 Renderer::Camera::GetViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}

void Renderer::Camera::ProcessKeyboard(CameraMovement direction, float deltaTime) {
    const float velocity = MovementSpeed * deltaTime;
    if (direction == CameraMovement::FORWARD)
        Position += Front * velocity;
    if (direction == CameraMovement::BACKWARD)
        Position -= Front * velocity;
    if (direction == CameraMovement::LEFT)
        Position -= Right * velocity;
    if (direction == CameraMovement::RIGHT)
        Position += Right * velocity;

    // make sure the user stays at the ground level
    //Position.y = 0.0f;
}

void Renderer::Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch /*= true*/) {
    if (Stopped_)
        return;

    xOffset *= MouseSensitivity;
    yOffset *= MouseSensitivity;

    Yaw += xOffset;
    Pitch += yOffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
}

void Renderer::Camera::ProcessMouseScroll(float yOffset) {
    if (Stopped_)
        return;

    Zoom = std::clamp(Zoom - yOffset, 1.0f, 45.0f);
}

void Renderer::Camera::Move(float delta, float x, float y) {
    if (Stopped_)
        return;

    if (x > 0) {
        ProcessKeyboard(CameraMovement::RIGHT, delta);
    }
    else if (x < 0) {
        ProcessKeyboard(CameraMovement::LEFT, delta);
    }
    if (y > 0) {
        ProcessKeyboard(CameraMovement::FORWARD, delta);
    }
    else if (y < 0) {
        ProcessKeyboard(CameraMovement::BACKWARD, delta);
    }
}

void Renderer::Camera::SwitchStopState() {
    Stopped_ = !Stopped_;

    LOG_ENGINE_DEBUG("Camera info: {}, {}, {}", Helpers::ToString(Position), Yaw, Pitch);
}

void Renderer::Camera::UpdateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}
