#include "SceneRenderer.h"

#include "ResourceManager.h"

SceneRenderer::SceneRenderer(::Camera* camera)
  : Camera(camera) {
    CubeRenderer.SetShader(ResourceManager::GetShader("textureShader"));
}

void SceneRenderer::Render(const std::vector<glm::vec3>& objects, unsigned width, unsigned height) const {
    // TODO: disable this for rendering multiple scenes
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // TODO: set matrices in uniform block for all shaders
    // camera may have moved, set new matrices
    ResourceManager::GetShader("textureShader")->SetMatrix4("view", Camera->GetViewMatrix());
    const glm::mat4 projection = glm::perspective(
        glm::radians(Camera->Zoom),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f, 100.0f
    );
    ResourceManager::GetShader("textureShader")->SetMatrix4("projection", projection);

    for (const auto& pos : objects) {
        CubeRenderer.DrawCube(ResourceManager::GetTexture2D("boxTexture"), pos);
    }
}
