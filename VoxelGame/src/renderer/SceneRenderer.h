#pragma once

#include "Camera.h"
#include "CubeRenderer.h"
#include "engine/Scene.h"
#include "engine/BlockFaces.h"
#include "light/DepthMap.h"
#include "light/ShadowMap.h"

namespace Renderer {
class SceneRenderer {
  private:
    Camera* Camera;
    std::map<Engine::Cube::BlockFaces, CubeRenderer> CubeRenderers_{};
    std::map<Engine::Cube::BlockFaces, unsigned> InstanceDataBufferIds_{};
    std::map<Engine::Cube::BlockFaces, size_t> BufferSizes_{};

    Shader* ShaderInstance_{nullptr};
    Shader* ShaderMesh_{nullptr};
    Shader* ShaderDepth_{ nullptr };
    Shader* ShaderDepthClosed_{ nullptr };

    DepthMap ShadowMap_;
    ShadowMap ShadowMapCSM_;

  public:
    explicit SceneRenderer(Renderer::Camera* camera);
    void Init();
    void Render(const Scene& scene, unsigned int width, unsigned int height);

  private:
    void RenderScene(const Scene& scene, Shader* shaderClosed, Shader* shaderOpen = nullptr);
    void RenderShadowMap(const Scene& scene);
    void BindInstancesData(const Scene& scene);
    void InitShaders(int levels);
};
} // namespace Renderer
