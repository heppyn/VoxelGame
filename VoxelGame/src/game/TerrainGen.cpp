#include "TerrainGen.h"

#include <perlin_noise/PerlinNoise.hpp>

#include "engine/ResourceManager.h"
#include "engine/Chunk.h"


Chunk Terrain::TerrainGen::GenerateChunk(const glm::vec2& position) {
    std::vector<GameObject> objects;
    const auto chunkSize = static_cast<unsigned>(Chunk::ChunkSize);
    objects.reserve(chunkSize * chunkSize);
    const siv::BasicPerlinNoise<float> perlin(0);

    for (unsigned int i = 0; i < chunkSize; ++i) {
        for (unsigned int j = 0; j < chunkSize; ++j) {
            const auto h = perlin.noise2D(
              (position.x + static_cast<float>(i)) / Chunk::ChunkSize,
              (position.y + static_cast<float>(j)) / Chunk::ChunkSize);
            objects.emplace_back(
              glm::vec3(position.x + static_cast<float>(i), std::floor(h * 10), position.y + static_cast<float>(j)),
              h > 0.0f ? glm::vec2(0, 0) : glm::vec2(0, 1),
              true);
        }
    }

    return Chunk(position, std::move(objects));
}
