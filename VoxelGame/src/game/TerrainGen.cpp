#include "TerrainGen.h"

#include "engine/ResourceManager.h"


std::vector<GameObject> Terrain::TerrainGen::GenerateChunk(const glm::vec2& position) {
    std::vector<GameObject> res;
    res.reserve(ChunkSize * ChunkSize);

    for (unsigned int i = 0; i < ChunkSize; ++i) {
        for (unsigned int j = 0; j < ChunkSize; ++j) {
            res.emplace_back(
              glm::vec3(position.x + static_cast<float>(i), 0.0f, position.y + static_cast<float>(j)),
              ResourceManager::GetTexture2D("boxTexture"));
        }
    }

    return res;
}
