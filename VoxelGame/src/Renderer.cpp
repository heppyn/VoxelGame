#include "Renderer.h"

#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL error] (" << error << "): " << function << " " << file << ":" << line << '\n';
        return false;
    }

    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    // TODO: check if index buffer is using different type
    GLCall(glDrawElements(GL_TRIANGLES, ib.Count(), GL_UNSIGNED_INT, nullptr));
}
