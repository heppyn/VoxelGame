#include "TerrainGen.h"

#include <algorithm>

#include "engine/ResourceManager.h"
#include "engine/Chunk.h"
#include "Terrain.h"
#include "BlockFactory.h"
#include "engine/Random.h"

Chunk Terrain::TerrainGen::GenerateChunk(const glm::vec2& position) {
    std::vector<GameObject> objects;
    const auto chunkSize = static_cast<unsigned>(Chunk::ChunkSize);
    objects.reserve(chunkSize * chunkSize);

    for (unsigned int i = 0; i < chunkSize; ++i) {
        for (unsigned int j = 0; j < chunkSize; ++j) {
            PlaceBlock(objects,
              glm::vec2(position.x + static_cast<float>(i), position.y + static_cast<float>(j)));
        }
    }

    objects.shrink_to_fit();
    return Chunk(position, std::move(objects));
}

void Terrain::TerrainGen::PlaceBlock(std::vector<GameObject>& buffer, const glm::vec2& pos) {
    auto h = static_cast<int>(BlockHeight(pos));
    const auto neigh = static_cast<int>(LowestNeigh(pos));

    do {
        buffer.emplace_back(
          BlockFactory::CreateBlock(
            glm::vec3(pos.x, static_cast<float>(h), pos.y),
            h > 0 ? BlockType::Stone : BlockType::Grass));
        --h;
    } while (h > neigh);
}

float Terrain::TerrainGen::LowestNeigh(const glm::vec2& pos) {
    return std::min({ BlockHeight({ pos.x - 1.0f, pos.y }),
      BlockHeight({ pos.x + 1.0f, pos.y }),
      BlockHeight({ pos.x, pos.y - 1.0f }),
      BlockHeight({ pos.x, pos.y + 1.0f }) });
}

float Terrain::TerrainGen::BlockHeight(const glm::vec2& pos) {
    return std::floor(
      30.0f * Engine::Random::Perlin.normalizedOctaveNoise2D(pos.x / Chunk::ChunkSize, pos.y / Chunk::ChunkSize, 2));
}
