#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture2D.h"
#include "Mesh.h"

namespace Renderer {
class CubeRenderer {
  public:
    CubeRenderer();
    CubeRenderer(const CubeRenderer&) = default;
    ~CubeRenderer();
    void DrawCube(const Mesh& mesh, const glm::vec3& position, const glm::vec3& scale) const;
    void DrawCube(Texture2D* texture, const glm::vec3& position) const;
    void DrawCubesBatched(const Mesh& mesh, unsigned int batchSize) const;
    void SetShader(Shader* shader) { Shader = shader; }

    static Mesh GetCubeMesh(bool batched = false);

  private:
    Shader* Shader{ nullptr };
    unsigned int CubeVao{ 0 };
    unsigned int CubeVbo{ 0 };
};
} // namespace Renderer
