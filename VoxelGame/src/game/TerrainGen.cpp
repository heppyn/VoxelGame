#include "TerrainGen.h"

#include <perlin_noise/PerlinNoise.hpp>

#include "engine/ResourceManager.h"
#include "engine/Chunk.h"
#include "Terrain.h"
#include "BlockFactory.h"

unsigned Terrain::TerrainGen::Seed_{ 0 };
std::random_device Terrain::TerrainGen::Random_{};

Chunk Terrain::TerrainGen::GenerateChunk(const glm::vec2& position) {
    if (!Seed_) {
        Seed_ = Random_();
    }

    std::vector<GameObject> objects;
    const auto chunkSize = static_cast<unsigned>(Chunk::ChunkSize);
    objects.reserve(chunkSize * chunkSize);
    const siv::BasicPerlinNoise<float> perlin(Seed_);

    for (unsigned int i = 0; i < chunkSize; ++i) {
        for (unsigned int j = 0; j < chunkSize; ++j) {
            const auto h = perlin.normalizedOctaveNoise2D(
              (position.x + static_cast<float>(i)) / Chunk::ChunkSize,
              (position.y + static_cast<float>(j)) / Chunk::ChunkSize,
                2);
            objects.emplace_back(
              BlockFactory::CreateBlock(
                glm::vec3(position.x + static_cast<float>(i), std::floor(h * 10), position.y + static_cast<float>(j)),
                h > 0.0f ? BlockType::Grass : BlockType::Stone));
        }
    }

    return Chunk(position, std::move(objects));
}
