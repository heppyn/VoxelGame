#include "CubeRenderer.h"

#include <algorithm>

#include "engine/Components/Mesh.h"
#include "engine/GameObject.h"
#include "engine/ResourceManager.h"


Renderer::CubeRenderer::~CubeRenderer() {
    glDeleteVertexArrays(1, &CubeVao);
}

void Renderer::CubeRenderer::Init() {
    DefaultMesh_ = GetCubeMesh(true);
}

void Renderer::CubeRenderer::DrawCube(const Mesh& mesh, const glm::vec3& position, const glm::vec3& scale) const {
    Shader->Use();

    // view and projection matrix are set once per frame
    glm::mat4 model = glm::mat4(1.0f); // identity matrix
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    // TODO: rotation
    Shader->SetMatrix4("model", model);

    mesh.Draw(*Shader);
}

void Renderer::CubeRenderer::DrawCubesBatched(unsigned amount) const {
    DefaultMesh_.DrawBatched(*Shader, amount);
}

void Renderer::CubeRenderer::DrawCubesBatched(const GameObject& go, unsigned amount) const {
    assert(go.HasComponent<Components::Mesh>());
    go.GetComponent<Components::Mesh>().Mesh_.DrawBatched(*Shader, amount);
}

Renderer::Mesh Renderer::CubeRenderer::GetCubeMesh(bool batched /*= false*/) {
    return GetCubeMesh({ 0, 0 }, batched);
}

Renderer::Mesh Renderer::CubeRenderer::GetCubeMesh(const glm::vec2& texPos, bool batched /*= false*/) {
    return GetCubeMeshFrom(Engine::Cube::ALL_SIDES, texPos, batched);
}

Renderer::Mesh Renderer::CubeRenderer::GetCubeMeshFrom(const Engine::Cube::BlockFaces& faces, glm::vec2 texPos, bool batched) {
    const auto& texSize = ResourceManager::GetSpriteSheetSize();
    texPos.y = texSize.y - 1 - texPos.y;

    return Mesh(GetVerticesWithTexture(texSize), GetIndicesFrom(faces), texPos, batched);
}

void Renderer::CubeRenderer::SetMeshFrom(const Engine::Cube::BlockFaces& faces) {
    DefaultMesh_ = GetCubeMeshFrom(faces);
}

std::vector<Renderer::Vertex> Renderer::CubeRenderer::GetVertices() {
    return {
        // clang-format off
        // pos                        // normals                 // tex
        // front
        { -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f },
        {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f },
        {  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f },
        { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 1.0f },
        // back
        { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f },
        {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f },
        {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f },
        { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f },
        // top
        { -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f },
        {  0.5f, 0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f },
        {  0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f },
        { -0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f },
        // bottom
        { -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f },
        {  0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f },
        {  0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f },
        { -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f },
        // right
        { 0.5f, -0.5f,   0.5f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f },
        { 0.5f, -0.5f,  -0.5f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f },
        { 0.5f,  0.5f,  -0.5f, 1.0f, 0.0f,  0.0f, 1.0f, 1.0f },
        { 0.5f,  0.5f,   0.5f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f },
        // left
        { -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
        { -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
        { -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f },
        { -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f },
        // clang-format on
    };
}

std::vector<Renderer::Vertex> Renderer::CubeRenderer::GetVerticesWithTexture(const glm::vec2& texSize) {
    auto vertices = GetVertices();

    std::ranges::for_each(vertices, [texSize](Vertex& v) {
        v.TexCoords = {
            v.TexCoords.x / texSize.x,
            v.TexCoords.y / texSize.y,
        };
    });

    return vertices;
}

std::vector<unsigned> Renderer::CubeRenderer::GetIndices() {
    return {
        // clang-format off
        // front
        0, 1, 3,
        1, 2, 3,
        // top
        8,  9, 11,
        11, 9, 10,
        // bottom
        12, 15, 14,
        12, 14, 13,
        // back
        7, 5, 4,
        7, 6, 5,
        // right
        16, 17, 19,
        17, 18, 19,
        // left
        20, 21, 23,
        21, 22, 23,
        // clang-format on
    };
}

std::vector<unsigned> Renderer::CubeRenderer::GetIndicesFrom(const Engine::Cube::BlockFaces& faces) {
    if (faces.HasFace(Engine::Cube::Faces::ALL)) {
        return GetIndices();
    }

    std::vector<unsigned> newIndices = {};
    std::vector<unsigned> allIndices = GetIndices();

    if (faces.HasFace(Engine::Cube::Faces::FRONT)) {
        newIndices.insert(newIndices.end(), allIndices.begin(), allIndices.begin() + 6);
    }
    if (faces.HasFace(Engine::Cube::Faces::TOP)) {
        newIndices.insert(newIndices.end(), allIndices.begin() + 6, allIndices.begin() + 12);
    }
    if (faces.HasFace(Engine::Cube::Faces::BOTTOM)) {
        newIndices.insert(newIndices.end(), allIndices.begin() + 12, allIndices.begin() + 18);
    }
    if (faces.HasFace(Engine::Cube::Faces::BACK)) {
        newIndices.insert(newIndices.end(), allIndices.begin() + 18, allIndices.begin() + 24);
    }
    if (faces.HasFace(Engine::Cube::Faces::RIGHT)) {
        newIndices.insert(newIndices.end(), allIndices.begin() + 24, allIndices.begin() + 30);
    }
    if (faces.HasFace(Engine::Cube::Faces::LEFT)) {
        newIndices.insert(newIndices.end(), allIndices.begin() + 30, allIndices.end());
    }

    return newIndices;
}
