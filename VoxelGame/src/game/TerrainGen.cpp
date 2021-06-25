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
    const auto surfHeight = BlockHeightSmooth(pos);
    const auto neighLow = static_cast<int>(LowestNeighSmooth(pos));
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
    } while (h > neighLow);
}

float Terrain::TerrainGen::LowestNeigh(const glm::vec2& pos) {
    const auto neigh = NeighHeights(pos);
    return *std::min_element(neigh.begin(), neigh.end());
}

float Terrain::TerrainGen::LowestNeighSmooth(const glm::vec2& pos) {
    const auto neigh = NeighHeightsSmooth(pos);
    return *std::min_element(neigh.begin(), neigh.end());
}

float Terrain::TerrainGen::HightestNeigh(const glm::vec2& pos) {
    const auto neigh = NeighHeights(pos);
    return *std::max_element(neigh.begin(), neigh.end());
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
      GetBaseHeight(pos) + heightVar * Engine::Random::Perlin.normalizedOctaveNoise2D_0_1(perPos.x, perPos.y, 2));
}

float Terrain::TerrainGen::BlockHeightSmooth(const glm::vec2& pos) {
    const auto high = static_cast<int>(HightestNeigh(pos));
    const auto low = static_cast<int>(LowestNeigh(pos));
    const auto h = static_cast<int>(BlockHeight(pos));

    if (const auto diff = std::abs(high - low); diff > 3) {
        if (std::abs(h - low) > std::abs(h - high))
            return std::floor(high - diff / 3.0f);
        return std::floor(low + diff / 3.0f);
    }

    return static_cast<float>(h);
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

std::vector<float> Terrain::TerrainGen::NeighHeights(const glm::vec2& pos) {
    return { BlockHeight({ pos.x - 1.0f, pos.y }),
        BlockHeight({ pos.x + 1.0f, pos.y }),
        BlockHeight({ pos.x, pos.y - 1.0f }),
        BlockHeight({ pos.x, pos.y + 1.0f }) };
}

std::vector<float> Terrain::TerrainGen::NeighHeightsSmooth(const glm::vec2& pos) {
    return { BlockHeightSmooth({ pos.x - 1.0f, pos.y }),
        BlockHeightSmooth({ pos.x + 1.0f, pos.y }),
        BlockHeightSmooth({ pos.x, pos.y - 1.0f }),
        BlockHeightSmooth({ pos.x, pos.y + 1.0f }) };
}
