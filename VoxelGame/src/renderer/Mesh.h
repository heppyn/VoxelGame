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

struct Texture {
    unsigned Id;
    std::string Type;
};

class Mesh {
  public:
    std::vector<Vertex> Vertices{};
    std::vector<unsigned int> Indices{};
    std::vector<Texture2D> Textures{};

    Mesh() = default;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture2D> textures, bool batched = false);
    void Draw(Shader& shader) const;

  private:
    unsigned Vao{ 0 }, Vbo{ 0 }, Ebo{ 0 };

    void SetupMesh(bool batched);
};
} // namespace Renderer
