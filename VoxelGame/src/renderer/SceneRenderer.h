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
    std::vector<glm::mat4> ModelMat{};
    unsigned int ModelMatBufferId{ 0 };

  public:
    explicit SceneRenderer(Renderer::Camera* camera);
    void Render(const Scene& scene, unsigned int width, unsigned int height);

  private:
    void CalculateModelMat(const std::vector<GameObject>& objects);
};
} // namespace Renderer
