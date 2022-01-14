#pragma once

#include "Camera.h"
#include "CubeRenderer.h"
#include "engine/Scene.h"


namespace Renderer {
class SceneRenderer {
  private:
    Camera* Camera;
    //CubeRenderer CubeRenderer{};
    std::map<Engine::Cube::BlockFaces, CubeRenderer> CubeRenderers_{};
    std::map<Engine::Cube::BlockFaces, unsigned> InstanceDataBufferIds_{};
    //unsigned int InstanceDataBufferId_{ 0 };
    std::map<Engine::Cube::BlockFaces, size_t> BufferSizes_{};
    //size_t BufferSize_{ 0 };

  public:
    explicit SceneRenderer(Renderer::Camera* camera);
    void Init();
    void Render(const Scene& scene, unsigned int width, unsigned int height);

  private:
    void BindInstancesData(const Scene& objects);
};
} // namespace Renderer
