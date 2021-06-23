#pragma once
#include <vector>

#include "Camera.h"
#include "CubeRenderer.h"
#include "engine/GameObject.h"
#include "engine/Scene.h"


namespace Renderer {
class SceneRenderer {
  private:
    Camera* Camera;
    CubeRenderer CubeRenderer{};
    unsigned int InstanceDataBufferId_{ 0 };

  public:
    explicit SceneRenderer(Renderer::Camera* camera);
    void Render(const Scene& scene, unsigned int width, unsigned int height);

  private:
    void BindInstancesData(const Scene& objects);
};
} // namespace Renderer
