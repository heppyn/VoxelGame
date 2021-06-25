#include "TerrainGen.h"

#include <algorithm>
#include <iostream>


#include "engine/ResourceManager.h"
#include "engine/Chunk.h"
#include "Terrain.h"
#include "Biome.h"
#include "BlockFactory.h"
#include "engine/Random.h"
#include "helpers/Math.h"

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
    const auto surfHeight = BlockHeight(pos);
    const auto neigh = static_cast<int>(LowestNeigh(pos));
    auto h = static_cast<int>(surfHeight);

    do {
        const glm::vec3 blockPos{
            pos.x, static_cast<float>(h), pos.y
        };
        buffer.emplace_back(
          BlockFactory::CreateBlock(
            blockPos,
            GetBlockType(blockPos, surfHeight)));
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
    const auto biome = Biome::GetBiome(pos);
    const auto heightVar = Biome::GetHeightVar(biome);
    const auto freq = Biome::GetFreq(biome);
    const glm::vec2 perPos = {
        pos.x / Chunk::ChunkSize / freq,
        pos.y / Chunk::ChunkSize / freq
    };

    return std::floor(
      heightVar * Engine::Random::Perlin.normalizedOctaveNoise2D_0_1(perPos.x, perPos.y, 2));
}

Terrain::BlockType Terrain::TerrainGen::GetBlockType(const glm::vec3& pos, float surfHeight) {
    const auto biome = Biome::GetBiome({ pos.x, pos.z });

    // stone below the surface
    if (pos.y + 3 <= surfHeight)
        return BlockType::Stone;

    switch (biome) {
        case BiomeType::Forrest:
            if (Helpers::Math::Equal(pos.y, surfHeight))
                return BlockType::GrassDark;
            return BlockType::Dirt;

        case BiomeType::Plains:
            if (Helpers::Math::Equal(pos.y, surfHeight))
                return BlockType::Grass;
            return BlockType::Dirt;

        case BiomeType::Desert:
            return BlockType::Sand;

        case BiomeType::Hills:
            return BlockType::Stone;
    }

    assert("Undefiend biome", false);
    return BlockType::Grass;
}
