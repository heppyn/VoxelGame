#include "SceneRenderer.h"

#include "engine/ResourceManager.h"
#include "engine/Components/Mesh.h"

Renderer::SceneRenderer::SceneRenderer(Renderer::Camera* camera)
  : Camera(camera) {}

void Renderer::SceneRenderer::Init() {
    // set up renderer with all sides, otherwise scene containing only light would crash
    CubeRenderers_[Engine::Cube::ALL_SIDES] = {};
    CubeRenderers_[Engine::Cube::ALL_SIDES].Init();
    InitShaders();
}

void Renderer::SceneRenderer::Render(const Scene& scene, unsigned width, unsigned height) {
    // TODO: check for change in terrain
    BindInstancesData(scene);

    // TODO: disable this for rendering multiple scenes
    glClearColor(103 / 255.0f, 157 / 255.0f, 245 / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto* shader : { ShaderInstance_, ShaderMesh_ }) {
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

    ShaderInstance_->SetVector3f("light.globalDir", scene.GetGlobalLight().Direction);
    ShaderInstance_->SetVector3f("light.global", scene.GetGlobalLight().Color);
    ShaderInstance_->SetVector3f("light.position", scene.GetLights().front().Position());
    ShaderInstance_->SetVector3f("view_pos", Camera->Position);

    // render all sides first
    glEnable(GL_CULL_FACE);
    if (scene.GetRenderableObjectsData().contains(Engine::Cube::ALL_SIDES)) {
        CubeRenderers_[Engine::Cube::ALL_SIDES].SetShader(ShaderInstance_);
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
        cubeRenderer.SetShader(ShaderInstance_);
        glBindBuffer(GL_ARRAY_BUFFER, InstanceDataBufferIds_[cube]);
        cubeRenderer.DrawCubesBatched(scene.GetSceneSize(cube));
    }

    // draw light separately
    // render with all sides
    assert(CubeRenderers_.contains(Engine::Cube::ALL_SIDES));
    CubeRenderers_[Engine::Cube::ALL_SIDES].SetShader(ShaderMesh_);
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

void Renderer::SceneRenderer::InitShaders() {
    ShaderInstance_ = ResourceManager::GetShader("lightBatch");
    ShaderMesh_ = ResourceManager::GetShader("meshShader");

    // set sprite sheet size for instancing
    ShaderInstance_->SetVector2f("tex_size", ResourceManager::GetSpriteSheetSize(), true);
    ShaderInstance_->SetVector3f("light.ambient", glm::vec3(0.25f));
    ShaderInstance_->SetVector3f("light.diffuse", glm::vec3(0.5f));
    ShaderInstance_->SetVector3f("light.specular", glm::vec3(1.0f));
    ShaderInstance_->SetFloat("material.shininess", 32.0f);

    // values taken from http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
    ShaderInstance_->SetFloat("light.constant", 1.0f);
    ShaderInstance_->SetFloat("light.linear", 0.027f);
    ShaderInstance_->SetFloat("light.quadratic", 0.0028f);
}
