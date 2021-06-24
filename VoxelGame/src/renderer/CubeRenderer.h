#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Mesh.h"

class GameObject;

namespace Renderer {
class CubeRenderer {
  public:
    CubeRenderer() = default;
    CubeRenderer(const CubeRenderer&) = default;
    ~CubeRenderer();
    void Init();
    void DrawCube(const Mesh& mesh, const glm::vec3& position, const glm::vec3& scale) const;
    void DrawCubesBatched(unsigned amount) const;
    void DrawCubesBatched(const GameObject& go, unsigned amount) const;
    void SetShader(Shader* shader) { Shader = shader; }
    [[nodiscard]] const Mesh& GetDefaultMesh() const { return DefaultMesh_; }

    [[nodiscard]] static Mesh GetCubeMesh(bool batched = false);
    [[nodiscard]] static Mesh GetCubeMesh(glm::vec2, bool batched = false);

  private:
    Shader* Shader{ nullptr };
    unsigned int CubeVao{ 0 };
    unsigned int CubeVbo{ 0 };
    Mesh DefaultMesh_{};

    [[nodiscard]] static std::vector<Vertex> GetVertices();
    [[nodiscard]] static std::vector<unsigned> GetIndices();
};
} // namespace Renderer
