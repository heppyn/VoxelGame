#include "Scene.h"

#include "ResourceManager.h"
#include "game/TerrainGen.h"

void Scene::Init() {
    const auto size = static_cast<int>(Terrain::TerrainGen::GetChunkSize());

    // add white light
    Lights_.emplace_back(glm::vec3(0.0f, 6.0f, 0.0f), ResourceManager::GetTexture2D("white"));
    Lights_.front().Scale(glm::vec3(0.25f));

    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            auto tmp = Terrain::TerrainGen::GenerateChunk(
              glm::vec2(static_cast<float>(i * size), static_cast<float>(j * size)));
            Objects_.insert(Objects_.end(), tmp.begin(), tmp.end());
        }
    }
}
