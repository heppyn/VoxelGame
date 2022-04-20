#include "TerrainGen.h"

#include <algorithm>

#include "engine/ResourceManager.h"
#include "engine/Chunk.h"
#include "Terrain.h"
#include "BlockFactory.h"
#include "vegetation/Tree.h"
#include "vegetation/TreeFactory.h"
#include "engine/Random.h"
#include "helpers/Math.h"
#include "vegetation/GrassFactory.h"

Terrain::Vegetation::GrassFactory Terrain::TerrainGen::GrassFactory_("./res/l-systems/plants/Grass.txt");

Chunk Terrain::TerrainGen::GenerateChunk(const glm::vec2& position) {
    const auto chunkSize = static_cast<unsigned>(Chunk::ChunkSize);
    Chunk chunk(position);
    chunk.GetObjects()[Chunk::DefaultCube_].reserve(chunkSize * chunkSize);
    chunk.GetObjectsTrans()[Vegetation::GrassFactory::GrassCube()].reserve(chunkSize * chunkSize);

    for (unsigned int i = 0; i < chunkSize; ++i) {
        for (unsigned int j = 0; j < chunkSize; ++j) {
            const auto pos =
              glm::vec2(position.x + static_cast<float>(j), position.y + static_cast<float>(i));

            const auto biome = PlaceBlock(chunk, pos);
            PlaceVegetation(chunk, pos, biome);
        }
    }

    chunk.FinisChunk();
    return chunk;
}

Terrain::BiomeType Terrain::TerrainGen::PlaceBlock(Chunk& chunk, const glm::vec2& pos) {
    const auto surfHeight = GetBlockHeight(pos);
    const auto neighLow = static_cast<int>(LowestNeigh(pos));
    auto h = static_cast<int>(surfHeight);
    const auto water = IsWater(surfHeight);

    // TODO: connect humidity to water near by
    const auto hum = GetHumidity(pos);
    const auto temp = GetTemperature({ pos.x, static_cast<float>(h), pos.y });
    const auto biome = water ? BiomeType::Water : Biome::GetBiome(pos, hum, temp);

    // set metadata to save chunk to a file
    SetBlockInfo(chunk, pos, hum, temp, biome, h);

    do {
        const glm::vec3 blockPos{
            pos.x, static_cast<float>(h), pos.y
        };
        chunk.AddObject(BlockFactory::CreateBlock(
          blockPos,
          GetBlockType(blockPos, surfHeight, biome)));
        --h;
    } while (h > neighLow);

    return biome;
}

void Terrain::TerrainGen::PlaceVegetation(Chunk& chunk, const glm::vec2& pos, BiomeType biome) {
    //TODO: call vegetation generation based on biome type. Return game object - not tree, grass, etc.
    const auto h = chunk.GetBlockInfo(pos).GetSurfaceHeight();

    if (auto tree = Vegetation::TreeFactory::GenerateTree({ pos.x, h, pos.y }, biome);
        !tree.empty()) {
        chunk.AddObjectData(std::move(tree));
        chunk.GetBlockInfo(pos).AddTree();
    }
    else {
        auto grass = Vegetation::GrassFactory::GenerateGrass({ pos.x, h, pos.y }, biome);
        chunk.AddObjectsTrans(std::move(grass), Vegetation::GrassFactory::GrassCube());
    }
}

void Terrain::TerrainGen::SetBlockInfo(Chunk& chunk, const glm::vec2& pos, Weather::Humidity humidity, Weather::Temperature temperature, BiomeType biome, int height) {
    auto& blockInfo = chunk.GetBlockInfo(pos);
    blockInfo.SetHumidity(humidity.Value);
    blockInfo.SetTemperature(temperature.Value);
    blockInfo.SetBiome(static_cast<unsigned>(biome));
    blockInfo.SetSurfaceHeight(height);
}

float Terrain::TerrainGen::LowestNeigh(const glm::vec2& pos) {
    const auto neigh = NeighHeights(pos);
    return *std::ranges::min_element(neigh);
}

Terrain::BlockType Terrain::TerrainGen::GetBlockType(const glm::vec3& pos, float surfHeight, BiomeType biome) {
    // stone below the surface
    if (pos.y + 3 <= surfHeight)
        return BlockType::Stone;

    if (biome != BiomeType::Water) {
        if (IsNextToWater(pos, 1.0f))
            return BlockType::Sand;

        if (IsNextToWater(pos, 2.0f) && Engine::Random::GetNoise0_1<float>(pos) > 0.35f)
            return BlockType::Sand;
    }


    switch (biome) {
        case BiomeType::Ice:
            return BlockType::Ice;

        case BiomeType::Tundra:
            if (Helpers::Math::Equal(pos.y, surfHeight))
                return BlockType::GrassTopTundra;
            return BlockType::Dirt;

        case BiomeType::Grassland:
            if (Helpers::Math::Equal(pos.y, surfHeight))
                return BlockType::GrassTop;
            return BlockType::Dirt;

        case BiomeType::ColdDesert:
            return BlockType::Greysand;

        case BiomeType::Woodland:
            if (Helpers::Math::Equal(pos.y, surfHeight))
                return BlockType::GrassTop;
            return BlockType::Dirt;

        case BiomeType::BorealForest:
            if (Helpers::Math::Equal(pos.y, surfHeight))
                return BlockType::GrassTop;
            return BlockType::Dirt;

        case BiomeType::Shrubland:
            if (Helpers::Math::Equal(pos.y, surfHeight))
                return BlockType::GravelDirt;
            return BlockType::Dirt;

        case BiomeType::SeasonalForest:
            if (Helpers::Math::Equal(pos.y, surfHeight))
                return BlockType::GrassTop;
            return BlockType::Dirt;

        case BiomeType::TemperateRainforest:
            if (Helpers::Math::Equal(pos.y, surfHeight))
                return BlockType::GrassTop;
            return BlockType::Dirt;

        case BiomeType::SubtropicalDesert:
            return BlockType::Sand;

        case BiomeType::TropicalForest:
            if (Helpers::Math::Equal(pos.y, surfHeight))
                return BlockType::GrassTopJungle;
            return BlockType::Dirt;

        case BiomeType::Savanna:
            if (Helpers::Math::Equal(pos.y, surfHeight))
                return BlockType::CottonRed;
            return BlockType::Dirt;

        case BiomeType::TropicalRainforest:
            if (Helpers::Math::Equal(pos.y, surfHeight))
                return BlockType::GrassTopJungle;
            return BlockType::Dirt;

        case BiomeType::Water:
            return BlockType::Water;
    }

    assert(false && "Undefiend biome");
    return BlockType::GrassTop;
}

std::vector<float> Terrain::TerrainGen::NeighHeights(const glm::vec2& pos) {
    return {
        GetBlockHeight({ pos.x - 1.0f, pos.y }),
        GetBlockHeight({ pos.x + 1.0f, pos.y }),
        GetBlockHeight({ pos.x, pos.y - 1.0f }),
        GetBlockHeight({ pos.x, pos.y + 1.0f })
    };
}

Weather::Humidity Terrain::TerrainGen::GetHumidity(const glm::vec2& pos) {
    // TODO: get humidity from surrounding water
    // add fuzzy transition
    const auto shift = static_cast<float>(Engine::Random::GetNoiseLimited(pos, Weather::NOISE));
    return {
        static_cast<unsigned char>(
          Engine::Random::Perlin.noise2D_0_1(
            (pos.x + shift) / Chunk::ChunkSize / 10.0f,
            (pos.y + shift) / Chunk::ChunkSize / 10.0f)
          * static_cast<float>(Weather::Humidity::SIZE - 1))
    };
}

Weather::Temperature Terrain::TerrainGen::GetTemperature(const glm::vec3& pos) {
    // size of all temperature bands
    constexpr auto tmpBandSize = 150;
    constexpr auto bandFluctuation = 15.0f;
    auto fluctuation = Engine::Random::Perlin.accumulatedOctaveNoise1D_0_1((pos.x + pos.z * 0.5f) * 0.1f, 2) * bandFluctuation;
    // add fuzzy transition
    fluctuation += static_cast<float>(Engine::Random::GetNoiseLimited(pos, Weather::NOISE));
    const auto dist = Helpers::Math::Mod(std::abs(pos.z) + fluctuation, tmpBandSize);
    Weather::Temperature temp{ 0 };

    // bands are repeating infinitely - determine if temperature should be rising or falling
    if ((static_cast<int>(std::abs(pos.z) + fluctuation) / tmpBandSize) % 2 == 0)
        temp = { static_cast<unsigned char>(Helpers::Math::Map(dist, 0, tmpBandSize - 1, Weather::Temperature::SIZE - 1, 0)) };
    else
        temp = { static_cast<unsigned char>(Helpers::Math::Map(dist, 0, tmpBandSize - 1, 0, Weather::Temperature::SIZE - 1)) };

    // take height into account
    const auto heightShift = static_cast<float>(Engine::Random::Get2dNoiseLimited(pos.x, pos.z, 3));
    const auto h = Helpers::Math::Map(pos.y + heightShift, 0.0f, MAX_BLOCK_HEIGHT, 0.0f, 1.0f);
    temp.Value -= static_cast<unsigned char>(h * static_cast<float>(Weather::Temperature::SIZE) * 0.5f);

    // temperature overflowed
    if (temp.Value >= Weather::Temperature::SIZE) {
        temp.Value = 0;
    }

    return temp;
}
