#pragma once
#include <vector>

#include "Camera.h"
#include "CubeRenderer.h"
#include "engine/GameObject.h"


namespace Renderer {
class SceneRenderer {
  public:
    explicit SceneRenderer(Camera* camera);
    void Render(const std::vector<GameObject>& objects, unsigned int width, unsigned int height) const;

  private:
    Camera* Camera;
    CubeRenderer CubeRenderer{};
};
} // namespace Renderer
