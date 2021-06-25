#include "Biome.h"

#include <cassert>

#include "engine/Chunk.h"
#include "engine/Random.h"

float Terrain::Biome::Frequency_{ 10.0f };

// TODO: load from file
float Terrain::Biome::GetFreq(BiomeType type) {
    switch (type) {
        case BiomeType::Plains:
            return 2.5f;
        case BiomeType::Forrest:
            return 2.0f;
        case BiomeType::Hills:
            return 1.0f;
        case BiomeType::Desert:
            return 1.5f;
    }

    assert("Undefined biome", false);
    return 1.0f;
}

float Terrain::Biome::GetHeightVar(BiomeType type) {
    switch (type) {
        case BiomeType::Plains:
            return 10.0f;
        case BiomeType::Forrest:
            return 8.0f;
        case BiomeType::Hills:
            return 30.0f;
        case BiomeType::Desert:
            return 14.0f;
    }

    assert("Undefined biome", false);
    return 1.0f;
}

Terrain::BiomeType Terrain::Biome::GetBiome(const glm::vec2& pos) {
    const auto val =
      Engine::Random::Perlin.noise2D_0_1(
        pos.x / Chunk::ChunkSize / Frequency_,
        pos.y / Chunk::ChunkSize / Frequency_);

    if (val <= 0.4f)
        return BiomeType::Plains;
    if (val <= 0.5f)
        return BiomeType::Forrest;
    if (val <= 0.6f)
        return BiomeType::Hills;

    return BiomeType::Desert;
}
