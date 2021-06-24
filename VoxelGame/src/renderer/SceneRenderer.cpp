#include "SceneRenderer.h"

#include "engine/ResourceManager.h"
#include "engine/Components/Mesh.h"

Renderer::SceneRenderer::SceneRenderer(Renderer::Camera* camera)
  : Camera(camera) {
    // default shader is the not batch one
}

void Renderer::SceneRenderer::Render(const Scene& scene, unsigned width, unsigned height) {
    // TODO: check for change in terrain
    BindInstancesData(scene);

    // TODO: disable this for rendering multiple scenes
    glClearColor(103/255.0f, 157/255.0f, 245/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::vector<Shader*> shaders = {
        ResourceManager::GetShader("meshShader"),
        ResourceManager::GetShader("light"),
        ResourceManager::GetShader("lightBatch"),
    };
    for (auto* shader : shaders) {
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
    for (auto i = 1; i <= 2; ++i) {
        // set sprite sheet size for instancing
        shaders[i]->SetVector2f("tex_size", ResourceManager::GetSpriteSheetSize(), true);

        shaders[i]->SetVector3f("light.globalDir", scene.GetGlobalLight().Direction);
        shaders[i]->SetVector3f("light.global", scene.GetGlobalLight().Color);
        shaders[i]->SetVector3f("light.ambient", glm::vec3(0.1f));
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
    CubeRenderer.DrawCubesBatched(
      scene.GetChunks().begin()->second.GetObjects().front(),
      scene.GetSceneSize());

    // draw light separately
    CubeRenderer.SetShader(shaders[0]);
    scene.GetLights().front().Draw(CubeRenderer);
}

void Renderer::SceneRenderer::BindInstancesData(const Scene& scene) {
    const auto instancesData = scene.GetRenderableObjectsData();
    const size_t objectsCnt = scene.GetSceneSize();

    // configure instanced array
    if (!InstanceDataBufferId_) {
        glGenBuffers(1, &InstanceDataBufferId_);
        glBindBuffer(GL_ARRAY_BUFFER, InstanceDataBufferId_);
        // allocate memory
        // TODO: reallocate for different number of objects
        glBufferData(
          GL_ARRAY_BUFFER,
          objectsCnt * sizeof(glm::mat4),
          nullptr,
          GL_DYNAMIC_DRAW);
    }

    // bind data
    glBindBuffer(GL_ARRAY_BUFFER, InstanceDataBufferId_);
    unsigned offset = 0;
    for (const auto& chunk : instancesData) {
        glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(glm::mat4), chunk->size() * sizeof(glm::mat4), chunk->data());
        offset += chunk->size();
    }

    const auto& firstChunkObjects = scene.GetChunks().begin()->second.GetObjects();
    if (!firstChunkObjects.empty()) {
        firstChunkObjects.front().GetComponent<Components::Mesh>().Mesh_.BindBatchAttribPtrs();
    }
}
