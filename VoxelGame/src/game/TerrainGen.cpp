#include "TerrainGen.h"

#include <cstdlib>
#include <ctime>

#include "engine/ResourceManager.h"


std::vector<GameObject> Terrain::TerrainGen::GenerateChunk(const glm::vec2& position) {
    std::vector<GameObject> res;
    res.reserve(ChunkSize * ChunkSize);
    std::srand(std::time(nullptr));

    for (unsigned int i = 0; i < ChunkSize; ++i) {
        for (unsigned int j = 0; j < ChunkSize; ++j) {
            const auto h = static_cast<float>(std::rand() / ((RAND_MAX + 1u) / 3));
            res.emplace_back(
              glm::vec3(position.x + static_cast<float>(i), 0.0f + h, position.y + static_cast<float>(j)),
              ResourceManager::GetTexture2D("boxTexture"),
              true);
            res.emplace_back(
              glm::vec3(position.x + static_cast<float>(i), 0.0f + h - 1, position.y + static_cast<float>(j)),
              ResourceManager::GetTexture2D("boxTexture"),
              true);
        }
    }

    return res;
}
