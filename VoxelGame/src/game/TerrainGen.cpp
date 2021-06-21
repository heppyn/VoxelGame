#include "TerrainGen.h"

#include <perlin_noise/PerlinNoise.hpp>

#include "engine/ResourceManager.h"


std::vector<GameObject> Terrain::TerrainGen::GenerateChunk(const glm::vec2& position) {
    std::vector<GameObject> res;
    res.reserve(ChunkSize * ChunkSize);
    const siv::BasicPerlinNoise<float> perlin(0);

    for (unsigned int i = 0; i < ChunkSize; ++i) {
        for (unsigned int j = 0; j < ChunkSize; ++j) {
            const auto h = perlin.noise2D(
              (position.x + static_cast<float>(i)) / static_cast<float>(ChunkSize),
              (position.y + static_cast<float>(j)) / static_cast<float>(ChunkSize));
            res.emplace_back(
              glm::vec3(position.x + static_cast<float>(i), std::floor(h * 10), position.y + static_cast<float>(j)),
              h > 0.0f ? glm::vec2(0, 0) : glm::vec2(0, 1),
              true);
        }
    }

    return res;
}
