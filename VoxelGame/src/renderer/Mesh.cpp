#include "Mesh.h"

#include <utility>

#include "../engine/ResourceManager.h"
#include "../helpers/Constants.h"


Renderer::Vertex::Vertex(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty)
  : Position(px, py, pz)
  , Normal(nx, ny, nz)
  , TexCoords(tx, ty) {
}

// Renderer::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture2D> textures, bool batched /*= false*/)
//   : Vertices(std::move(vertices)),
//     Indices(std::move(indices)),
//     Textures(std::move(textures)) {
//     SetupMesh(batched);
// }

Renderer::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, const glm::vec2& texPos, bool batched)
  : Vertices(std::move(vertices))
  , Indices(std::move(indices))
  , TexPos_(texPos) {
    SetupMesh(batched);
}

// Renderer::Mesh::Mesh(const Mesh& other)
//   : Vertices(other.Vertices), Indices(other.Indices), Textures(other.Textures), Vao(other.Vao), Vbo(other.Vbo), Ebo(other.Ebo) {
// }
//
// Renderer::Mesh& Renderer::Mesh::operator=(const Mesh& other) {
//     if (this != &other) {
//         Vertices = other.Vertices;
//         Indices = other.Indices;
//         Textures = other.Textures;
//     }
//
//     return *this;
// }

Renderer::Mesh::Mesh(Mesh&& other) noexcept
  : Vertices(std::move(other.Vertices))
  , Indices(std::move(other.Indices))
  , Textures(std::move(other.Textures))
  , Vao(other.Vao)
  , Vbo(other.Vbo)
  , Ebo(other.Ebo)
  , TexPos_(other.TexPos_) {
}

Renderer::Mesh& Renderer::Mesh::operator=(Mesh&& other) noexcept {
    if (this != &other) {
        Vertices = std::move(other.Vertices);
        Indices = std::move(other.Indices);
        Textures = std::move(other.Textures);
        Vao = other.Vao;
        Vbo = other.Vbo;
        Ebo = other.Ebo;
        TexPos_ = other.TexPos_;
    }

    return *this;
}

void Renderer::Mesh::Draw(Shader& shader) const {
    assert(Vao);
    shader.Use();
    BindTextures(shader);

    // draw mesh
    glBindVertexArray(Vao);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(Indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // set to default
    glActiveTexture(GL_TEXTURE0);
}

void Renderer::Mesh::DrawBatched(Shader& shader, unsigned amount) const {
    assert(Vao);
    shader.Use();
    BindSpriteSheets(shader);

    glBindVertexArray(Vao);
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(Indices.size()), GL_UNSIGNED_INT, 0, amount);
    glBindVertexArray(0);

    // set to default
    glActiveTexture(GL_TEXTURE0);
}

void Renderer::Mesh::SetupMesh(bool batched) {
    glGenVertexArrays(1, &Vao);
    glGenBuffers(1, &Vbo);
    glGenBuffers(1, &Ebo);

    glBindVertexArray(Vao);
    glBindBuffer(GL_ARRAY_BUFFER, Vbo);

    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), Vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned), Indices.data(), GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    if (batched) {
        BindBatchAttribPtrs();
    }

    glBindVertexArray(0);
}

void Renderer::Mesh::BindTextures(Shader& shader) const {
    // only diffuse texture present - unbind others
    // https://stackoverflow.com/questions/28411686/opengl-reading-from-unbound-texture-unit
    if (Textures.size() == 1) {
        UnbindTextures(4);
    }
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < Textures.size(); i++) {
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = Textures[i].Type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);

        // now set the sampler to the correct texture unit
        shader.SetInteger((name + number).c_str(), i);
        // and finally bind the texture
        Textures[i].Bind(i);
    }
}

void Renderer::Mesh::BindSpriteSheets(Shader& shader) const {
    // set sampler to the correct texture unit
    shader.SetInteger("texture_diffuse1", 0);
    ResourceManager::GetTexture2D(Constants::SPRITE_SHEET.c_str())->Bind(0);

    if (auto* spriteSheet = ResourceManager::GetTexture2D(Constants::SPRITE_SHEET_SPEC.c_str());
        spriteSheet) {
        shader.SetInteger("texture_specular1", 1);
        spriteSheet->Bind(1);
    }
}

void Renderer::Mesh::UnbindTextures(unsigned num) const {
    for (unsigned i = 0; i < num; ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Renderer::Mesh::BindMesh() const {
    glBindVertexArray(Vao);
}

void Renderer::Mesh::BindBatchAttribPtrs() const {
    glBindVertexArray(Vao);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
}

const glm::vec2& Renderer::Mesh::GetTexPos() const {
    return TexPos_;
}
