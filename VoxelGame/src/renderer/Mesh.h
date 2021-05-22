#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture2D.h"


namespace Renderer {
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

    Vertex(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty);
};

class Mesh {
  public:
    std::vector<Vertex> Vertices{};
    std::vector<unsigned int> Indices{};
    // TODO: set default "missing texture"
    std::vector<Texture2D> Textures{};

    Mesh() = default;
    ~Mesh() = default;
    //Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture2D> textures, bool batched = false);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, const glm::vec2& texPos, bool batched = false);
    Mesh(const Mesh& other) = default;
    Mesh& operator=(const Mesh& other) = default;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;
    void Draw(Shader& shader) const;
    void DrawBatched(Shader& shader, unsigned amount) const;
    void BindMesh() const;
    void BindBatchAttribPtrs() const;

    [[nodiscard]] const glm::vec2& GetTexPos() const;

  private:
    unsigned Vao{ 0 }, Vbo{ 0 }, Ebo{ 0 };
    // TODO: is this needed?
    glm::vec2 TexPos_ = { 0, 0 };

    void SetupMesh(bool batched);
    void BindTextures(Shader& shader) const;
    void BindSpriteSheets(Shader& shader) const;
    void UnbindTextures(unsigned num) const;
};
} // namespace Renderer
