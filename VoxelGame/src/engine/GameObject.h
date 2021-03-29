#pragma once
#include "glm/vec3.hpp"
#include "renderer/CubeRenderer.h"
#include "renderer/Texture2D.h"

class GameObject {
  private:
    glm::vec3 Position{ 0 };
    // TODO: set default "missing texture"
    Renderer::Texture2D* Texture{ nullptr };

  public:
    GameObject() = default;
    GameObject(glm::vec3 position, Renderer::Texture2D* texture);

    virtual void Draw(const Renderer::CubeRenderer& renderer) const;
};
