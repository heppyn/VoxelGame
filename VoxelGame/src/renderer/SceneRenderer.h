#pragma once
#include <vector>

#include "Camera.h"
#include "CubeRenderer.h"
#include "engine/GameObject.h"
#include "engine/Scene.h"


namespace Renderer {
namespace Detail {
    struct InstanceData {
        glm::mat4 ModelMat;
        glm::vec4 TexCoords;
    };
} // namespace Detail

class SceneRenderer {
  private:
    Camera* Camera;
    CubeRenderer CubeRenderer{};
    std::vector<Detail::InstanceData> InstancesData_{};
    unsigned int InstanceDataBufferId_{ 0 };

  public:
    explicit SceneRenderer(Renderer::Camera* camera);
    void Render(const Scene& scene, unsigned int width, unsigned int height);

  private:
    void CalculateInstanceData(const std::vector<GameObject>& objects);
};
} // namespace Renderer
