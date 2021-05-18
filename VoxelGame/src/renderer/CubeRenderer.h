#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture2D.h"
#include "Mesh.h"

class GameObject;

namespace Renderer {
class CubeRenderer {
  public:
    CubeRenderer() = default;
    CubeRenderer(const CubeRenderer&) = default;
    ~CubeRenderer();
    void DrawCube(const Mesh& mesh, const glm::vec3& position, const glm::vec3& scale) const;
    void DrawCubesBatched(const GameObject& go, unsigned amount) const;
    void SetShader(Shader* shader) { Shader = shader; }

    static Mesh GetCubeMesh(bool batched = false);

  private:
    Shader* Shader{ nullptr };
    unsigned int CubeVao{ 0 };
    unsigned int CubeVbo{ 0 };
};
} // namespace Renderer
