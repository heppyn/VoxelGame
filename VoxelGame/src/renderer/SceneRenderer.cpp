#include "SceneRenderer.h"

#include "engine/ResourceManager.h"

Renderer::SceneRenderer::SceneRenderer(Renderer::Camera* camera)
  : Camera(camera) {
    // default shader is the not batch one
    CubeRenderer.SetShader(ResourceManager::GetShader("textureShader"));
}

void Renderer::SceneRenderer::Render(const Scene& scene, unsigned width, unsigned height) {
    if (ModelMat.empty()) {
        // TODO: check for change in terrain
        CalculateModelMat(scene.GetObjects());
    }
    // TODO: disable this for rendering multiple scenes
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //auto* shader = ResourceManager::GetShader("tBatchShader");
    //auto* shader = ResourceManager::GetShader("textureShader");
    std::vector<Shader*> shaders = {
        ResourceManager::GetShader("meshShader"),
        ResourceManager::GetShader("light"),
    };
    for (auto *shader : shaders) {
        // TODO: set matrices in uniform block for all shaders
        // camera may have moved, set new matrices
        shader->SetMatrix4("view", Camera->GetViewMatrix(), true);
        const glm::mat4 projection = glm::perspective(
          glm::radians(Camera->Zoom),
          static_cast<float>(width) / static_cast<float>(height),
          0.1f,
          100.0f);
        shader->SetMatrix4("projection", projection);
        //shader->SetVector3f("light_color", 1.0f, 1.0f, 1.0f);
        shader->SetVector3f("light_color", 0.5f, 0.5f, 0.5f);
        shader->SetVector3f("light_pos", scene.GetLights().front().GetPosition());
        shader->SetVector3f("view_pos", Camera->Position);
    }

    CubeRenderer.SetShader(shaders[1]);
    //CubeRenderer.DrawCubesBatched(objects.front().GetTexture(), ModelMat.size());

    // render one object at a time
    for (const auto& o : scene.GetObjects()) {
        o.Draw(CubeRenderer);
    }

    // draw light separately
    CubeRenderer.SetShader(shaders[0]);
    scene.GetLights().front().Draw(CubeRenderer);
}

void Renderer::SceneRenderer::CalculateModelMat(const std::vector<GameObject>& objects) {
    for (const auto& o : objects) {
        ModelMat.emplace_back(glm::translate(glm::mat4(1.0f), o.GetPosition()));
    }

    // configure instanced array
    glGenBuffers(1, &ModelMatBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, ModelMatBufferId);
    glBufferData(GL_ARRAY_BUFFER, ModelMat.size() * sizeof(glm::mat4), ModelMat.data(), GL_STATIC_DRAW);
}
