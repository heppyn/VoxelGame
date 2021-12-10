#include "Scene.h"

#include <iostream>
#include <utility>
#include <GLFW/glfw3.h>

#include "helpers/Constants.h"
#include "ResourceManager.h"
#include "Components/SpritesheetTex.h"
#include "game/TerrainGen.h"
#include "L-systems/LSystemExecutor.h"
#include "L-systems/LSystemParser.h"

void Scene::Init(std::shared_ptr<Renderer::Camera> camera) {
    SetCamera(std::move(camera));

    // add white light
    Lights_.emplace_back(glm::vec3(100.0f, 30.0f, 0.0f), ResourceManager::GetTexture2D("white"));
    Lights_.front().Scale(glm::vec3(0.25f));

    // generate first chunks around the camera
    Update();
}

void Scene::UpdateOrig() {
    if (Chunks_.empty()) {
        LSystems::LSystemExecutor ge(0, 0.0f);
        const auto lSystems = LSystems::LSystemParser::LoadLSystemFromFile("./res/l-systems/plants/Grass2D.txt");
        if (!lSystems.empty()) {
            Chunk chunk(glm::vec2(0.0f));
            auto pos = glm::vec3(0.0f);
            for (const auto& lSystem : lSystems) {
                auto objects = ge.GenerateBasedOn(pos, lSystem, 0.3f, 7, 2);
                for (auto& o : objects[0]) {
                    o.AddComponent<Components::SpritesheetTex>(glm::vec2(1.0f, 0.0f));
                }
                chunk.GetObjects().insert(chunk.GetObjects().end(), std::make_move_iterator(objects[0].begin()), std::make_move_iterator(objects[0].end()));

                pos += glm::vec3(30.0f, 0.0f, 0.0f);
            }
            chunk.FinisChunk();
            ObjectsDataCache_.push_back(chunk.GetInstancesData());
            Chunks_.emplace(glm::vec2(0.0f), std::move(chunk));
        }
        else {
            std::cout << "Failed to load L-system\n";
        }
    }
}


void Scene::Update() {
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
            if (glfwGetTime() - startTime > Constants::FRAME_LEN) {
                overFrame = true;
                break;
            }
            const auto chunkPos = glm::vec2(
              centerChunkPos.x + static_cast<float>(i) * Chunk::ChunkSize,
              centerChunkPos.y + static_cast<float>(j) * Chunk::ChunkSize);
            if (!Chunks_.contains(chunkPos)) {
                const auto startTimeChunk = glfwGetTime();
                Chunks_.emplace(chunkPos, Terrain::TerrainGen::GenerateChunk(chunkPos));
                updated = true;
                std::cout << "Chunk generated in " << (glfwGetTime() - startTimeChunk) * 1000.0 << " ms\n";
            }
        }
        if (overFrame)
            break;
    }

    if (updated)
        UpdateObjectsData();
}

void Scene::SetCamera(std::shared_ptr<Renderer::Camera> camera) {
    Camera_ = std::move(camera);
}

const std::map<glm::vec2, Chunk, Helpers::CmpGlmVec<glm::vec2>>& Scene::GetChunks() const {
    return Chunks_;
}

std::vector<std::shared_ptr<std::vector<glm::mat4>>> Scene::GetRenderableObjectsData() const {
    return ObjectsDataCache_;
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

void Scene::UpdateObjectsData() {
    ObjectsDataCache_.clear();
    const auto centerChunkPos = GetCenterChunkPos();

    for (auto i = -RenderDistance_; i <= RenderDistance_; ++i) {
        for (auto j = -RenderDistance_; j <= RenderDistance_; ++j) {
            const auto chunkPos = glm::vec2(
              centerChunkPos.x + static_cast<float>(i) * Chunk::ChunkSize,
              centerChunkPos.y + static_cast<float>(j) * Chunk::ChunkSize);
            if (Chunks_.contains(chunkPos)) {
                ObjectsDataCache_.push_back(Chunks_.at(chunkPos).GetInstancesData());
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
            if (Chunks_.contains(chunkPos)) {
                ObjectsDataCache_.push_back(Chunks_.at(chunkPos).GetInstancesDataTrans());
            }
        }
    }
}

bool Scene::IsInRenderDistance(const Chunk& chunk) const {
    const auto centerChunkPos = GetCenterChunkPos();
    const float distance = static_cast<float>(RenderDistance_) * Chunk::ChunkSize;

    return centerChunkPos.x - distance <= chunk.Position.x
           && centerChunkPos.x + distance >= chunk.Position.x
           && centerChunkPos.y - distance <= chunk.Position.y
           && centerChunkPos.y + distance >= chunk.Position.y;
}
