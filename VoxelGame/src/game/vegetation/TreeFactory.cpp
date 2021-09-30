#include "TreeFactory.h"

#include "engine/Random.h"
#include "Tree.h"


bool Terrain::Vegetation::TreeFactory::HasTree(const glm::vec3& pos, BiomeType biome) {
    // octaves determine density of the forest
    // frequency of the noise
    switch (biome) {
        case BiomeType::TropicalForest:
        case BiomeType::TropicalRainforest:
        case BiomeType::TemperateRainforest:
        case BiomeType::Tundra:
            return Engine::Random::IsLocalMaxPerlin(pos, FREQ_DENSE, DENSITY_DENSE);

        case BiomeType::Ice:
        case BiomeType::ColdDesert:
        case BiomeType::SubtropicalDesert:
        case BiomeType::Shrubland:
            return false;

        case BiomeType::Grassland:
            return Engine::Random::IsLocalMaxPerlin(pos, FREQ_SPARSE, DENSITY_SPARSE);

        case BiomeType::Woodland:
        case BiomeType::SeasonalForest:
        case BiomeType::BorealForest:
            return Engine::Random::IsLocalMaxPerlin(pos, FREQ_NORMAL, DENSITY_NORMAL);

        case BiomeType::Savanna:
            return Engine::Random::IsLocalMaxPerlin(pos, FREQ_NORMAL, DENSITY_DENSE);
    }

    assert(false);
    return false;
}

std::vector<GameObject> Terrain::Vegetation::TreeFactory::GenerateTree(const glm::vec3& pos, BiomeType biome) {
    if (!HasTree(pos,biome)) {
        return {};
    }

    switch (biome) {
        // has no trees
        case BiomeType::Ice:
        case BiomeType::ColdDesert:
            return {};

        case BiomeType::Tundra:
        case BiomeType::Grassland:
        case BiomeType::BorealForest:
        case BiomeType::Shrubland:
        case BiomeType::SeasonalForest:
        case BiomeType::TemperateRainforest:
        case BiomeType::SubtropicalDesert:
        case BiomeType::Savanna:
            return {};

        case BiomeType::Woodland:
            return Tree::SpawnNormalTree(pos);

        case BiomeType::TropicalForest:
        case BiomeType::TropicalRainforest:
            return Tree::SpawnJungleTree(pos);
    }

    assert(false);
    return {};
}
