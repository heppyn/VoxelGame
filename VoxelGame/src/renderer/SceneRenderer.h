#pragma once

#include "Camera.h"
#include "CubeRenderer.h"
#include "engine/Scene.h"
#include "engine/BlockFaces.h"


namespace Renderer {
class SceneRenderer {
  private:
    Camera* Camera;
    std::map<Engine::Cube::BlockFaces, CubeRenderer> CubeRenderers_{};
    std::map<Engine::Cube::BlockFaces, unsigned> InstanceDataBufferIds_{};
    std::map<Engine::Cube::BlockFaces, size_t> BufferSizes_{};

  public:
    explicit SceneRenderer(Renderer::Camera* camera);
    void Init();
    void Render(const Scene& scene, unsigned int width, unsigned int height);

  private:
    void BindInstancesData(const Scene& scene);
};
} // namespace Renderer
