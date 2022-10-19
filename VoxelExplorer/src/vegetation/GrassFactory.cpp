#include "GrassFactory.h"

#include <engine/Random.h>
#include <engine/L-systems/LSystemParser.h>
#include <helpers/Print.h>


Terrain::BlockFactory Terrain::Vegetation::GrassFactory::BlockFactory_(glm::vec3(0.5f), { 0.0f, -0.25f, 0.f });

Terrain::Vegetation::GrassFactory::GrassFactory(std::string_view grassFile)
  : LSystems_(LSystems::LSystemParser::LoadLSystemFromFile(grassFile)) {
}

std::vector<GameObject> Terrain::Vegetation::GrassFactory::GenerateGrass(const glm::vec3& pos, BiomeType biome) {
    const glm::vec3 newPos = { pos.x, pos.y + 1.0f, pos.z };
    std::vector<GameObject> res;
    if (HasGrass(newPos, biome)) {
        const auto r = Engine::Random::Get3dNoise0_1<float>(newPos.x, newPos.y, newPos.z);
        constexpr auto numGrass = 4.0f;
        if (r < 1.0f / numGrass) {
            res.emplace_back(BlockFactory_.CreateFromPreset(newPos, BlockType::Grass1));
        }
        else if (r < 2.0f / numGrass) {
            res.emplace_back(BlockFactory_.CreateFromPreset(newPos, BlockType::Grass2));
        }
        else if (r < 3.0f / numGrass) {
            res.emplace_back(BlockFactory_.CreateFromPreset(newPos, BlockType::Grass3));
        }
        else {
            res.emplace_back(BlockFactory_.CreateFromPreset(newPos, BlockType::Grass4));
        }
    }

    return res;
}

std::vector<GameObject> Terrain::Vegetation::GrassFactory::GenerateLSystemGrass(const glm::vec3& pos, BiomeType biome) {
    if (HasGrass(pos, biome)) {
        const glm::vec3 newPos = {
            pos.x + (Engine::Random::Get2dNoise0_1<float>(pos.x, pos.y) - 0.5f),
            pos.y,
            pos.z + (Engine::Random::Get2dNoise0_1<float>(pos.x, pos.z) - 0.5f)
        };
        return std::move(LExecutor_.GenerateBasedOn(
          newPos,
          LSystems_[Engine::Random::GetNoiseLimited(pos, LSystems_.size())],
          0.05f,
          2,
          Engine::Random::GetNoise(pos))[0]);
    }
    return {};
}

bool Terrain::Vegetation::GrassFactory::HasGrass(const glm::vec3& pos, BiomeType biome) {
    switch (GetGrassDensity(biome)) {
        case GrassDensity::Dense:
            return Engine::Random::GetNoise0_1<float>(pos) > 0.2f;
        case GrassDensity::Normal:
            return Engine::Random::GetNoise0_1<float>(pos) > 0.5f;
        case GrassDensity::Sparse:
            return Engine::Random::GetNoise0_1<float>(pos) > 0.8f;
        case GrassDensity::None:
            return false;
    }

    assert(false);
    return false;
}

Terrain::Vegetation::GrassDensity Terrain::Vegetation::GrassFactory::GetGrassDensity(BiomeType biome) {
    switch (biome) {
        case BiomeType::Ice:
        case BiomeType::ColdDesert:
        case BiomeType::SubtropicalDesert:
        case BiomeType::Water:
            return GrassDensity::None;

        case BiomeType::Tundra:
            return GrassDensity::Sparse;

        case BiomeType::Woodland:
        case BiomeType::BorealForest:
        case BiomeType::SeasonalForest:
        case BiomeType::TemperateRainforest:
        case BiomeType::TropicalForest:
        case BiomeType::Savanna:
        case BiomeType::TropicalRainforest:
            return GrassDensity::Normal;

        case BiomeType::Grassland:
        case BiomeType::Shrubland:
            return GrassDensity::Dense;
    }

    assert(false);
    return GrassDensity::None;
}
