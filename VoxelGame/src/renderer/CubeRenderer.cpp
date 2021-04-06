#include "CubeRenderer.h"

Renderer::CubeRenderer::CubeRenderer() {
    //InitRenderData();
    //InitBatchRenderData();
}

Renderer::CubeRenderer::~CubeRenderer() {
    glDeleteVertexArrays(1, &CubeVao);
}

void Renderer::CubeRenderer::DrawCube(const Mesh& mesh, const glm::vec3& position) const
{
    Shader->Use();

    // view and projection matrix are set once per frame
    glm::mat4 model = glm::mat4(1.0f); // identity matrix
    model = glm::translate(model, position);

    // TODO: scaling and rotation
    Shader->SetMatrix4("model", model);

    mesh.Draw(*Shader);
}

void Renderer::CubeRenderer::DrawCube(Texture2D* texture, const glm::vec3& position) const {
    // TODO: cache shader and texture binding
    Shader->Use();
    texture->Bind();

    // view and projection matrix are set once per frame
    glm::mat4 model = glm::mat4(1.0f); // identity matrix
    model = glm::translate(model, position);

    // TODO: scaling and rotation
    Shader->SetMatrix4("model", model);

    // TODO: share vertex array for all cubes
    glBindVertexArray(CubeVao);
    // TODO: QL_QUADS
    // 36 = 6 * 2 * 3
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Renderer::CubeRenderer::DrawCubesBatched(Texture2D* texture, unsigned batchSize) const {
    // TODO: cache shader and texture binding
    Shader->Use();
    texture->Bind();

    //GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, CubeVbo));
    glBindVertexArray(CubeVao);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, batchSize);
    //glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr, batchSize);
    glBindVertexArray(0);
}

Renderer::Mesh Renderer::CubeRenderer::GetCubeMesh()
{
    std::vector<Vertex> vertices = {
        // clang-format off
        // pos                        // normals                 // tex
        // front
        { -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
        {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
        {  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
        { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
        // back
        { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
        {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
        {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
        { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
        // top
        { -0.5f, 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
        {  0.5f, 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
        {  0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
        { -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
        // bottom
        { -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
        {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
        {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
        { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
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
        //7, 3, 2,
        //7, 2, 6,
        // left
        7, 4, 0,
        7, 0, 3,
        // right
        2, 1, 5,
        2, 5, 6,
        // bottom
        12, 15, 14,
        12, 14, 13,
        //0, 4, 5,
        //0, 5, 1,
        // back
        7, 5, 4,
        7, 6, 5,
        // clang-format on
    };

    return Mesh(vertices, indices, {});
}

void Renderer::CubeRenderer::InitRenderData() {
    unsigned int vbo;
    float vertices[] = {
        // clang-format off
        // pos                // tex  
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        // clang-format on
    };
    glGenVertexArrays(1, &CubeVao);
    glGenBuffers(1, &CubeVbo);

    glBindBuffer(GL_ARRAY_BUFFER, CubeVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(CubeVao);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // can you have it here?
    //glDeleteBuffers(1, &vbo);
}

void Renderer::CubeRenderer::InitBatchRenderData() const {
    glBindVertexArray(CubeVao);
    // set attribute pointer for matrix -> 4 x vec4
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glBindVertexArray(0);
}
