#include "TerrainGen.h"

#include <cstdlib>
#include <ctime>

#include "engine/ResourceManager.h"


std::vector<GameObject> Terrain::TerrainGen::GenerateChunk(const glm::vec2& position) {
    std::vector<GameObject> res;
    res.reserve(ChunkSize * ChunkSize);
    std::srand(std::time(nullptr));
    const std::vector<Renderer::Texture2D*> textures = {
        ResourceManager::GetTexture2D("box"),
        ResourceManager::GetTexture2D("boxSpec"),
    };
    auto* concrete = ResourceManager::GetTexture2D("concrete");

    for (unsigned int i = 0; i < ChunkSize; ++i) {
        for (unsigned int j = 0; j < ChunkSize; ++j) {
            const auto r = std::rand() / ((RAND_MAX + 1u) / 10);
            res.emplace_back(
              glm::vec3(position.x + static_cast<float>(i), 0.0f, position.y + static_cast<float>(j)),
              glm::vec2(0, 1),
              true);
            if (r % 10 == 0) {
                res.emplace_back(
                  glm::vec3(position.x + static_cast<float>(i), 1.0f, position.y + static_cast<float>(j)),
                  glm::vec2(0, 0),
                  true);
            }
        }
    }

    return res;
}
