#include "Scene.h"

#include <utility>

#include "ResourceManager.h"
#include "game/TerrainGen.h"

void Scene::Init(std::shared_ptr<Renderer::Camera> camera) {
    SetCamera(std::move(camera));

    // add white light
    Lights_.emplace_back(glm::vec3(0.0f, 6.0f, 0.0f), ResourceManager::GetTexture2D("white"));
    Lights_.front().Scale(glm::vec3(0.25f));

    // generate first chunks around the camera
    Update();
}

void Scene::Update() {
    const auto centerChunkPos = GetCenterChunkPos();

    for (auto i = -RenderDistance_; i <= RenderDistance_; ++i) {
        for (auto j = -RenderDistance_; j <= RenderDistance_; ++j) {
            const auto chunkPos = glm::vec2(
              centerChunkPos.x + static_cast<float>(i) * Chunk::ChunkSize,
              centerChunkPos.y + static_cast<float>(j) * Chunk::ChunkSize);
            if (!Chunks_.contains(chunkPos)) {
                Chunks_.emplace(chunkPos, Terrain::TerrainGen::GenerateChunk(chunkPos));
            }
        }
    }
}

void Scene::SetCamera(std::shared_ptr<Renderer::Camera> camera) {
    Camera_ = std::move(camera);
}

const std::map<glm::vec2, Chunk, Helpers::CmpGlmVec<glm::vec2>>& Scene::GetChunks() const {
    return Chunks_;
}

std::vector<std::shared_ptr<std::vector<glm::mat4>>> Scene::GetRenderableObjectsData() const {
    // TODO: add caching
    std::vector<std::shared_ptr<std::vector<glm::mat4>>> objectsData;

    const auto centerChunkPos = GetCenterChunkPos();

    for (auto i = -RenderDistance_; i <= RenderDistance_; ++i) {
        for (auto j = -RenderDistance_; j <= RenderDistance_; ++j) {
            const auto chunkPos = glm::vec2(
              centerChunkPos.x + static_cast<float>(i) * Chunk::ChunkSize,
              centerChunkPos.y + static_cast<float>(j) * Chunk::ChunkSize);
            assert(Chunks_.contains(chunkPos));

            objectsData.push_back(Chunks_.at(chunkPos).GetInstancesData());
        }
    }

    return objectsData;
}

size_t Scene::GetSceneSize() const {
    size_t size = 0;
    for (const auto& chunk : GetRenderableObjectsData()) {
        size += chunk->size();
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
