#include "CubeRenderer.h"

#include "engine/Components/Mesh.h"
#include "engine/GameObject.h"


Renderer::CubeRenderer::~CubeRenderer() {
    glDeleteVertexArrays(1, &CubeVao);
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

void Renderer::CubeRenderer::DrawCubesBatched(const GameObject& go, unsigned amount) const
{
    assert(go.HasComponent<Components::Mesh>());
    go.GetComponent<Components::Mesh>().Mesh_.DrawBatched(*Shader, amount);
}

Renderer::Mesh Renderer::CubeRenderer::GetCubeMesh(bool batched /*= false*/) {
    std::vector<Vertex> vertices = {
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
        { -0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f },
        {  0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f },
        {  0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f },
        { -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
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
        { -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f, 0.0f, 0.0f },
        { -0.5f, -0.5f,  0.5f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f },
        { -0.5f,  0.5f,  0.5f, -1.0f, 0.0f,  0.0f, 1.0f, 1.0f },
        { -0.5f,  0.5f, -0.5f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f },
        // clang-format on
    };

    std::vector<unsigned> indices = {
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

    return Mesh(vertices, indices, {}, batched);
}
