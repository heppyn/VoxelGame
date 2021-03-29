#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture2D.h"

namespace Renderer {
class CubeRenderer {
  public:
    CubeRenderer();
    CubeRenderer(const CubeRenderer&) = default;
    ~CubeRenderer();
    void DrawCube(Texture2D* texture, const glm::vec3& position) const;
    void SetShader(Shader* shader) { Shader = shader; }

  private:
    Shader* Shader{ nullptr };
    unsigned int CubeVao{ 0 };

    void InitRenderData();
};
} // namespace Renderer
