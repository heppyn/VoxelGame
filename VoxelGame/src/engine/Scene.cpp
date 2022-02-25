#include "Scene.h"

#include <iostream>
#include <utility>
#include <GLFW/glfw3.h>

#include "helpers/Constants.h"
#include "ResourceManager.h"
#include "Components/SpritesheetTex.h"
#include "game/TerrainGen.h"

#include "examples/ExampleScene.h"
#include "open_gl/WindowManagerGl.h"

void Scene::Init(std::shared_ptr<Renderer::Camera> camera) {
    SetCamera(std::move(camera));

    // add white light
    Lights_.emplace_back(glm::vec3(100.0f, 30.0f, 0.0f), ResourceManager::GetTexture2D("white"));
    Lights_.front().Scale(glm::vec3(0.25f));

    // generate first chunks around the camera
    Update();
}

void Scene::UpdateOrig(bool updateAll /*= false*/) {
    if (Chunks_.empty()) {
        Chunks_.emplace(glm::vec2(0.0f), ExampleScene::Shadow());

        UpdateObjectsData();
    }
}

void Scene::Update(bool updateAll /*= false*/) {
    const auto startTime = glfwGetTime();
    const auto centerChunkPos = GetCenterChunkPos();
    auto updated{ false };

    // deallocate chunk out of render distance
    for (auto it = Chunks_.begin(), nextIt = it; it != Chunks_.end(); it = nextIt) {
        ++nextIt;
        if (!IsInRenderDistance(it->second)) {
            //std::cout << "Erasing chunk at:" << it->first.x << ", " << it->first.y << '\n';
            Chunks_.erase(it);
            updated = true;
        }
    }

    auto overFrame = false;
    for (auto i = -RenderDistance_; i <= RenderDistance_; ++i) {
        for (auto j = -RenderDistance_; j <= RenderDistance_; ++j) {
            // pause world generation if frame rate would drop
            overFrame = glfwGetTime() - startTime > Constants::FRAME_LEN;
            if (overFrame && !updateAll) {
                break;
            }
            const auto chunkPos = glm::vec2(
              centerChunkPos.x + static_cast<float>(i) * Chunk::ChunkSize,
              centerChunkPos.y + static_cast<float>(j) * Chunk::ChunkSize);
            if (!Chunks_.contains(chunkPos)) {
                const auto startTimeChunk = glfwGetTime();
                Chunks_.emplace(chunkPos, Terrain::TerrainGen::GenerateChunk(chunkPos));
                updated = true;
                //std::cout << "Chunk generated in " << (glfwGetTime() - startTimeChunk) * 1000.0 << " ms\n";
            }
        }
        if (overFrame && !updateAll)
            break;
    }

    // Camera might have moved - update renderable objects
    UpdateObjectsData();
}

void Scene::SetCamera(std::shared_ptr<Renderer::Camera> camera) {
    Camera_ = std::move(camera);
}

const std::map<glm::vec2, Chunk, Helpers::CmpGlmVec<glm::vec2>>& Scene::GetChunks() const {
    return Chunks_;
}

const std::map<Engine::Cube::BlockFaces, std::vector<std::shared_ptr<std::vector<glm::mat4>>>>& Scene::GetRenderableObjectsData() const {
    return ObjectsDataCache_;
}

size_t Scene::GetSceneSize(const Engine::Cube::BlockFaces& faces) const {
    size_t size = 0;
    if (!GetRenderableObjectsData().contains(faces))
        return 0;

    for (const auto& chunkObjects : GetRenderableObjectsData().at(faces)) {
        size += chunkObjects->size();
    }

    return size;
}

glm::vec2 Scene::GetCenterChunkPos() const {
    return glm::vec2(
      Camera_->Position.x > 0.0f ? floor(Camera_->Position.x / Chunk::ChunkSize) * Chunk::ChunkSize
                                 : ceil(Camera_->Position.x / Chunk::ChunkSize) * Chunk::ChunkSize,
      Camera_->Position.z > 0.0f ? floor(Camera_->Position.z / Chunk::ChunkSize) * Chunk::ChunkSize
                                 : ceil(Camera_->Position.z / Chunk::ChunkSize) * Chunk::ChunkSize);
}

void Scene::UpdateObjectsData() {
    ObjectsDataCache_.clear();
    const auto centerChunkPos = GetCenterChunkPos();
    const auto viewProj = ViewProjMatrix();

    for (auto i = -RenderDistance_; i <= RenderDistance_; ++i) {
        for (auto j = -RenderDistance_; j <= RenderDistance_; ++j) {
            const auto chunkPos = glm::vec2(
              centerChunkPos.x + static_cast<float>(i) * Chunk::ChunkSize,
              centerChunkPos.y + static_cast<float>(j) * Chunk::ChunkSize);

            // TODO: fix bug, where top of the trees disappears
            // always include chunk in which the player is standing
            if (Chunks_.contains(chunkPos)
                && (IsChunkInView(Chunks_.at(chunkPos).PositionInSpace(), viewProj) || i == 0 && j == 0)) {
                for (const auto& [cube, data] : Chunks_.at(chunkPos).GetInstancesData()) {
                    ObjectsDataCache_[cube].push_back(data);
                }
            }
        }
    }
    // render transparent objects last
    // this ensures correct color blending for semi transparent textures
    // TODO: add chunks from the furthest to the closest one this will ensure correct blending
    for (auto i = -RenderDistance_; i <= RenderDistance_; ++i) {
        for (auto j = -RenderDistance_; j <= RenderDistance_; ++j) {
            const auto chunkPos = glm::vec2(
              centerChunkPos.x + static_cast<float>(i) * Chunk::ChunkSize,
              centerChunkPos.y + static_cast<float>(j) * Chunk::ChunkSize);

            // always include chunk in which the player is standing
            if (Chunks_.contains(chunkPos)
                && (IsChunkInView(Chunks_.at(chunkPos).PositionInSpace(), viewProj) || i == 0 && j == 0)) {
                for (const auto& [cube, data] : Chunks_.at(chunkPos).GetInstancesDataTrans()) {
                    ObjectsDataCache_[cube].push_back(data);
                }
            }
        }
    }
}

glm::mat4 Scene::ViewProjMatrix() const {
    const auto view = Camera_->GetViewMatrix();
    const auto proj = glm::perspective(
      glm::radians(Camera_->Zoom),
      static_cast<float>(WindowManagerGl::Width) / static_cast<float>(WindowManagerGl::Height),
      0.1f,
      500.0f);
    return proj * view;
}

bool Scene::IsInRenderDistance(const Chunk& chunk) const {
    const auto centerChunkPos = GetCenterChunkPos();
    const float distance = static_cast<float>(RenderDistance_) * Chunk::ChunkSize;

    return centerChunkPos.x - distance <= chunk.Position.x
           && centerChunkPos.x + distance >= chunk.Position.x
           && centerChunkPos.y - distance <= chunk.Position.y
           && centerChunkPos.y + distance >= chunk.Position.y;
}

bool Scene::IsChunkInView(const glm::vec3& position, const glm::mat4& viewProj) {
    // define order of corner checking
    for (const auto& c :
      { glm::vec2(0.0f), glm::vec2(1.0f), glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 1.0f) }) {
        // position is in the center of the block
        const auto corner = glm::vec2(position.x - 0.5f + Chunk::ChunkSize * c.x, position.z - 0.5f + Chunk::ChunkSize * c.y);

        auto pt = viewProj * glm::vec4(corner.x, position.y, corner.y, 1.0f);
        pt /= pt.w;

        if (pt.x >= -1.0f && pt.x <= 1.0f && pt.z <= 1.0f)
            return true;
    }

    return false;
}
