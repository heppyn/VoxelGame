#pragma once
#include "Camera.h"
#include "CubeRenderer.h"

class SceneRenderer {
  public:
    explicit SceneRenderer(Camera* camera);
    void Render(const std::vector<glm::vec3>& objects, unsigned int width, unsigned int height) const;

  private:
    Camera* Camera;
    Renderer::CubeRenderer CubeRenderer{};
};
