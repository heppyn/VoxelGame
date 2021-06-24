#pragma once

#include "Camera.h"
#include "CubeRenderer.h"
#include "engine/Scene.h"


namespace Renderer {
class SceneRenderer {
  private:
    Camera* Camera;
    CubeRenderer CubeRenderer{};
    unsigned int InstanceDataBufferId_{ 0 };
    size_t BufferSize_{ 0 };

  public:
    explicit SceneRenderer(Renderer::Camera* camera);
    void Init();
    void Render(const Scene& scene, unsigned int width, unsigned int height);

  private:
    void BindInstancesData(const Scene& objects);
};
} // namespace Renderer
