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
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
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
    }

    // only light shader
    shaders[1]->SetVector3f("light.ambient", glm::vec3(0.1f));
    shaders[1]->SetVector3f("light.diffuse", glm::vec3(0.5f));
    shaders[1]->SetVector3f("light.specular", glm::vec3(1.0f));
    shaders[1]->SetVector3f("light.position", scene.GetLights().front().GetPosition());
    shaders[1]->SetFloat("material.shininess", 32.0f);
    shaders[1]->SetVector3f("view_pos", Camera->Position);

    // values taken from http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
    shaders[1]->SetFloat("light.constant", 1.0f);
    shaders[1]->SetFloat("light.linear", 0.027f);
    shaders[1]->SetFloat("light.quadratic", 0.0028f);

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
