#include "GrassFactory.h"

#include "engine/Random.h"

Terrain::BlockFactory Terrain::Vegetation::GrassFactory::BlockFactory_(glm::vec3(0.5f), { 0.0f, -0.25f, 0.f });


std::vector<GameObject> Terrain::Vegetation::GrassFactory::GenerateGrass(const glm::vec3& pos, BiomeType biome) {
    constexpr auto scale = 0.5f;
    std::vector<GameObject> res;
    if (HasGrass(pos, biome)) {
        const auto r = Engine::Random::Get3dNoise0_1<float>(pos.x, pos.y, pos.z);
        constexpr auto numGrass = 4.0f;
        if (r < 1.0f / numGrass) {
            res.emplace_back(BlockFactory_.CreateFromPreset(pos, BlockType::Grass1));
        }
        else if (r < 2.0f / numGrass) {
            res.emplace_back(BlockFactory_.CreateFromPreset(pos, BlockType::Grass2));
        }
        else if (r < 3.0f / numGrass) {
            res.emplace_back(BlockFactory_.CreateFromPreset(pos, BlockType::Grass3));
        }
        else {
            res.emplace_back(BlockFactory_.CreateFromPreset(pos, BlockType::Grass4));
        }
    }

    return res;
}

bool Terrain::Vegetation::GrassFactory::HasGrass(const glm::vec3& pos, BiomeType biome) {
    switch (GetGrassDensity(biome)) {
        case GrassDensity::Dense:
            return Engine::Random::Get3dNoise0_1<float>(pos.x, pos.y, pos.z) > 0.2f;
        case GrassDensity::Normal:
            return Engine::Random::Get3dNoise0_1<float>(pos.x, pos.y, pos.z) > 0.5f;
        case GrassDensity::Sparse:
            return Engine::Random::Get3dNoise0_1<float>(pos.x, pos.y, pos.z) > 0.8f;
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
