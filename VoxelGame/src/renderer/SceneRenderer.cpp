#include "SceneRenderer.h"

#include "engine/ResourceManager.h"
#include "engine/Components/Mesh.h"

Renderer::SceneRenderer::SceneRenderer(Renderer::Camera* camera)
  : Camera(camera) {
    // default shader is the not batch one
}

void Renderer::SceneRenderer::Render(const Scene& scene, unsigned width, unsigned height) {
    if (ModelMat.empty()) {
        // TODO: check for change in terrain
        CalculateModelMat(scene.GetObjects());
    }
    // TODO: disable this for rendering multiple scenes
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::vector<Shader*> shaders = {
        ResourceManager::GetShader("meshShader"),
        ResourceManager::GetShader("light"),
        ResourceManager::GetShader("lightBatch"),
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
    for (auto i = 1; i <= 2; ++i)
    {
        shaders[i]->SetVector3f("light.ambient", glm::vec3(0.1f), true);
        shaders[i]->SetVector3f("light.diffuse", glm::vec3(0.5f));
        shaders[i]->SetVector3f("light.specular", glm::vec3(1.0f));
        shaders[i]->SetVector3f("light.position", scene.GetLights().front().Position());
        shaders[i]->SetFloat("material.shininess", 32.0f);
        shaders[i]->SetVector3f("view_pos", Camera->Position);

        // values taken from http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
        shaders[i]->SetFloat("light.constant", 1.0f);
        shaders[i]->SetFloat("light.linear", 0.027f);
        shaders[i]->SetFloat("light.quadratic", 0.0028f);
    }

    // render all objects at once
    CubeRenderer.SetShader(shaders[2]);
    CubeRenderer.DrawCubesBatched(scene.GetObjects().front(), ModelMat.size());

    // render one object at a time
    //CubeRenderer.SetShader(shaders[1]);
    //for (const auto& o : scene.GetObjects()) {
    //    o.Draw(CubeRenderer);
    //}

    // draw light separately
    CubeRenderer.SetShader(shaders[0]);
    scene.GetLights().front().Draw(CubeRenderer);
}

void Renderer::SceneRenderer::CalculateModelMat(const std::vector<GameObject>& objects) {
    for (const auto& o : objects) {
        auto model = glm::mat4(1.0f); // identity matrix
        model = glm::translate(model, o.Position());
        model = glm::scale(model, o.Scale());
        ModelMat.push_back(model);
    }

    // configure instanced array
    glGenBuffers(1, &ModelMatBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, ModelMatBufferId);
    glBufferData(GL_ARRAY_BUFFER, ModelMat.size() * sizeof(glm::mat4), ModelMat.data(), GL_STATIC_DRAW);

    if (!objects.empty())
    {
        objects.front().GetComponent<Components::Mesh>().Mesh_.BindBatchAttribPtrs();
    }
}
