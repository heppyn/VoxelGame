#include "SceneRenderer.h"

#include "engine/ResourceManager.h"
#include "engine/Components/Mesh.h"

Renderer::SceneRenderer::SceneRenderer(Renderer::Camera* camera)
  : Camera(camera) {
    // default shader is the not batch one
}

void Renderer::SceneRenderer::Init() {
    // set up renderer with all sides, otherwise scene containing only light would crash
    CubeRenderers_[Engine::Cube::ALL_SIDES] = {};
    CubeRenderers_[Engine::Cube::ALL_SIDES].Init();
}

void Renderer::SceneRenderer::Render(const Scene& scene, unsigned width, unsigned height) {
    // TODO: check for change in terrain
    BindInstancesData(scene);

    // TODO: disable this for rendering multiple scenes
    glClearColor(103 / 255.0f, 157 / 255.0f, 245 / 255.0f, 1.0f);
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
        // size of frustum
        const glm::mat4 projection = glm::perspective(
          glm::radians(Camera->Zoom),
          static_cast<float>(width) / static_cast<float>(height),
          0.1f,
          500.0f);
        shader->SetMatrix4("projection", projection);
    }

    // only light shader
    for (auto i = 1; i <= 2; ++i) {
        // set sprite sheet size for instancing
        shaders[i]->SetVector2f("tex_size", ResourceManager::GetSpriteSheetSize(), true);

        shaders[i]->SetVector3f("light.globalDir", scene.GetGlobalLight().Direction);
        shaders[i]->SetVector3f("light.global", scene.GetGlobalLight().Color);
        shaders[i]->SetVector3f("light.ambient", glm::vec3(0.25f));
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

    // render all sides first
    glEnable(GL_CULL_FACE);
    if (scene.GetRenderableObjectsData().contains(Engine::Cube::ALL_SIDES)) {
        CubeRenderers_[Engine::Cube::ALL_SIDES].SetShader(shaders[2]);
        glBindBuffer(GL_ARRAY_BUFFER, InstanceDataBufferIds_[Engine::Cube::ALL_SIDES]);
        CubeRenderers_[Engine::Cube::ALL_SIDES].DrawCubesBatched(scene.GetSceneSize(Engine::Cube::ALL_SIDES));
    }

    // disable face culling - all sides can be seen
    glDisable(GL_CULL_FACE);
    // render objects depending on cube sides
    for (auto& [cube, cubeRenderer] : CubeRenderers_) {
        if (cube == Engine::Cube::ALL_SIDES)
            continue;

        // render all objects at once
        cubeRenderer.SetShader(shaders[2]);
        glBindBuffer(GL_ARRAY_BUFFER, InstanceDataBufferIds_[cube]);
        cubeRenderer.DrawCubesBatched(scene.GetSceneSize(cube));
    }

    // draw light separately
    // render with all sides
    assert(CubeRenderers_.contains(Engine::Cube::ALL_SIDES));
    CubeRenderers_[Engine::Cube::ALL_SIDES].SetShader(shaders[0]);
    scene.GetLights().front().Draw(CubeRenderers_[Engine::Cube::ALL_SIDES]);
}

void Renderer::SceneRenderer::BindInstancesData(const Scene& scene) {
    for (const auto& instancesDataMap = scene.GetRenderableObjectsData();
        const auto& [cube, instancesData] : instancesDataMap) {
        const size_t newSize = 3 * sizeof(glm::mat4) * scene.GetSceneSize(cube);

        // configure instanced array
        if (!InstanceDataBufferIds_.contains(cube)) {
            glGenBuffers(1, &InstanceDataBufferIds_[cube]);
            glBindBuffer(GL_ARRAY_BUFFER, InstanceDataBufferIds_[cube]);

            // create cube renderer first time cube with x sides is used
            CubeRenderers_[cube] = {};
            CubeRenderers_[cube].SetMeshFrom(cube);
        }

        // allocate memory
        if (!BufferSizes_.contains(cube) || BufferSizes_[cube] < newSize) {
            BufferSizes_[cube] = newSize;

            glBindBuffer(GL_ARRAY_BUFFER, InstanceDataBufferIds_[cube]);
            glBufferData(
              GL_ARRAY_BUFFER,
              static_cast<long>(BufferSizes_[cube]),
              nullptr,
              GL_STATIC_DRAW);
        }

        // bind data
        glBindBuffer(GL_ARRAY_BUFFER, InstanceDataBufferIds_[cube]);
        unsigned offset = 0;
        for (const auto& chunk : instancesData) {
            glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(glm::mat4), chunk->size() * sizeof(glm::mat4), chunk->data());
            offset += chunk->size();
        }

        CubeRenderers_[cube].GetDefaultMesh().BindBatchAttribPtrs();
    }
}
