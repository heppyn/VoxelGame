#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "engine/BlockFaces.h"

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
    [[nodiscard]] static Mesh GetCubeMesh(const glm::vec2& texPos, bool batched = false);
    [[nodiscard]] static Mesh GetCubeMeshFrom(
      const Engine::Cube::BlockFaces& faces,
      glm::vec2 texPos = { 0.0f, 0.0f },
      bool batched = false);

    void SetMeshFrom(const Engine::Cube::BlockFaces& faces);

  private:
    Shader* Shader{ nullptr };
    unsigned int CubeVao{ 0 }; // TODO: delete
    unsigned int CubeVbo{ 0 }; // TODO: delete
    Mesh DefaultMesh_{};

    [[nodiscard]] static std::vector<Vertex> GetVertices();
    [[nodiscard]] static std::vector<Vertex> GetVerticesWithTexture(const glm::vec2& texSize);
    [[nodiscard]] static std::vector<unsigned> GetIndices();
    [[nodiscard]] static std::vector<unsigned> GetIndicesFrom(const Engine::Cube::BlockFaces& faces);
};
} // namespace Renderer
