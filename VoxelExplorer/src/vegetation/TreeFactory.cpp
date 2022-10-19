#include "TreeFactory.h"

#include <engine/Random.h>

#include "Tree.h"


bool Terrain::Vegetation::TreeFactory::HasTree(const glm::vec3& pos, BiomeType biome) {
    return CanHaveTree(pos, biome) && !HasNeighTree(pos, biome, 1);
}

std::vector<glm::mat4> Terrain::Vegetation::TreeFactory::GenerateTree(const glm::vec3& pos, BiomeType biome) {
    if (!HasTree(pos, biome)) {
        return {};
    }

    switch (biome) {
        // has no trees
        case BiomeType::Ice:
        case BiomeType::ColdDesert:
            return {};

        case BiomeType::Tundra:
        case BiomeType::BorealForest:
        case BiomeType::SeasonalForest:
        case BiomeType::TemperateRainforest:
            return {};

        case BiomeType::Shrubland:
            return Tree::SpawnLSystemShrub(pos);

        case BiomeType::SubtropicalDesert:
            return Tree::SpawnLSystemCactus(pos);

        case BiomeType::Savanna:
            return Tree::SpawnLSystemSavannaTree(pos);

        case BiomeType::Grassland:
        case BiomeType::Woodland:
            return Tree::SpawnLSystemNormalTree(pos);

        case BiomeType::TropicalForest:
        case BiomeType::TropicalRainforest:
            return Tree::SpawnLSystemJungleTree(pos);
    }

    assert(false);
    return {};
}

bool Terrain::Vegetation::TreeFactory::HasNeighTree(const glm::vec3& pos, BiomeType biome, int regionSize) {
    // check on positive coordinates to preserve determinism
    // TODO: fix biome change on border
    assert(regionSize > 0);
    for (int i = 0; i <= regionSize; ++i) {
        for (int j = 0; j <= regionSize; ++j) {
            if (i == 0 && j == 0)
                continue;
            if (CanHaveTree({ pos.x + static_cast<float>(i), pos.y, pos.z + static_cast<float>(j) }, biome)) {
                return true;
            }
        }
    }

    return false;
}

bool Terrain::Vegetation::TreeFactory::CanHaveTree(const glm::vec3& pos, BiomeType biome) {
    // octaves determine density of the forest
    // frequency of the noise
    switch (biome) {
        case BiomeType::TropicalForest:
        case BiomeType::TropicalRainforest:
        case BiomeType::TemperateRainforest:
        case BiomeType::Tundra:
            return Engine::Random::IsLocalMaxPerlin({pos.x, pos.z}, FREQ_NORMAL * 1.5f, DENSITY_DENSE);

        case BiomeType::Ice:
        case BiomeType::ColdDesert:
        case BiomeType::Water:
            return false;

        case BiomeType::SubtropicalDesert:
            return Engine::Random::IsLocalMaxPerlin({ pos.x, pos.z }, FREQ_RARE, DENSITY_SPARSE);

        case BiomeType::Grassland:
            return Engine::Random::IsLocalMaxPerlin({ pos.x, pos.z }, FREQ_RARE * 2.2f, DENSITY_SPARSE);

        case BiomeType::Woodland:
        case BiomeType::SeasonalForest:
        case BiomeType::BorealForest:
            return Engine::Random::IsLocalMaxPerlin({ pos.x, pos.z }, FREQ_NORMAL, DENSITY_NORMAL);

        case BiomeType::Shrubland:
            return Engine::Random::IsLocalMaxPerlin({ pos.x, pos.z }, FREQ_SPARSE / 1.9f, DENSITY_DENSE);
        case BiomeType::Savanna:
            return Engine::Random::IsLocalMaxPerlin({ pos.x, pos.z }, FREQ_RARE * 1.5f, DENSITY_DENSE);
    }

    assert(false && "Undefined biome");
    return false;
}
