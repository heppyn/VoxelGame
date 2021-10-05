#include "Biome.h"

#include <cassert>

#include "engine/Chunk.h"
#include "engine/Random.h"

float Terrain::Biome::Frequency_{ 10.0f };
std::vector<std::vector<std::vector<Terrain::BiomeType>>> Terrain::Biome::BiomeTable_{};


// TODO: load from file
float Terrain::Biome::GetFreq(BiomeType type) {
    return 2.5f;
    // TODO: revisit this based on height map
    //switch (type) {
    //    case BiomeType::Plains:
    //        return 2.5f;
    //    case BiomeType::Forrest:
    //        return 2.0f;
    //    case BiomeType::Hills:
    //        return 1.0f;
    //    case BiomeType::Desert:
    //        return 1.5f;
    //}

    //assert("Undefined biome", false);
    //return 1.0f;
}

float Terrain::Biome::GetHeightVar(BiomeType type) {
    return 10.0f;
    // TODO: revisit this based on height map
    /*switch (type) {
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
    return 1.0f;*/
}

Terrain::BiomeType Terrain::Biome::GetBiome(const glm::vec2& pos, Weather::Humidity humidity, Weather::Temperature temperature) {
    constexpr auto zoneSize = 128.0f;
    // TODO: initialize before this call and assert not empty
    if (BiomeTable_.empty()) {
        InitBiomeTable();
    }

    assert(Weather::Humidity::SIZE == BiomeTable_.size());
    assert(Weather::Temperature::SIZE == BiomeTable_[0].size());

    // pick from possible biomes
    // TODO: prefer biomes that match their neighbors
    const auto index = static_cast<size_t>(
      static_cast<float>(BiomeTable_[humidity.Value][temperature.Value].size())
      * Engine::Random::Perlin.accumulatedOctaveNoise2D_0_1(pos.x / zoneSize, pos.y / zoneSize, 1));
    return BiomeTable_[humidity.Value][temperature.Value][index];
}

void Terrain::Biome::Init() {
    InitBiomeTable();
}

void Terrain::Biome::Clear() {
    BiomeTable_.clear();
}


void Terrain::Biome::InitBiomeTable() {
    // Table[humidity][temperature][biome number]
    using enum BiomeType;
    BiomeTable_ = {
        {
          { Ice },
          { Tundra },
          { Grassland, ColdDesert },
          { Grassland, ColdDesert },
          { Grassland, ColdDesert },
          { SubtropicalDesert },
          { SubtropicalDesert },
          { SubtropicalDesert },
          { SubtropicalDesert },
          { SubtropicalDesert },
        },
        {
          { Ice },
          { Tundra },
          { Grassland, ColdDesert },
          { Grassland, ColdDesert },
          { Grassland, ColdDesert },
          { Grassland, ColdDesert },
          { SubtropicalDesert },
          { SubtropicalDesert },
          { SubtropicalDesert },
          { SubtropicalDesert },
        },
        {
          { Ice },
          { Tundra },
          { Grassland, ColdDesert },
          { Grassland, ColdDesert },
          { Grassland, ColdDesert },
          { Grassland, ColdDesert },
          { SubtropicalDesert },
          { SubtropicalDesert },
          { SubtropicalDesert },
          { SubtropicalDesert },
        },
        {
          { Ice },
          { Tundra },
          { Woodland, Shrubland },
          { Woodland, Shrubland },
          { Woodland, Shrubland },
          { Grassland, ColdDesert },
          { TropicalForest, Savanna },
          { TropicalForest, Savanna },
          { TropicalForest, Savanna },
          { TropicalForest, Savanna },
        },
        {
          { Ice },
          { Tundra },
          { Woodland, Shrubland },
          { Woodland, Shrubland },
          { Woodland, Shrubland },
          { Woodland, Shrubland },
          { TropicalForest, Savanna },
          { TropicalForest, Savanna },
          { TropicalForest, Savanna },
          { TropicalForest, Savanna },
        },
        {
          { Ice },
          { Tundra },
          { BorealForest },
          { SeasonalForest },
          { Woodland, Shrubland },
          { Woodland, Shrubland },
          { TropicalForest, Savanna },
          { TropicalForest, Savanna },
          { TropicalForest, Savanna },
          { TropicalForest, Savanna },
        },
        {
          { Ice },
          { Tundra },
          { BorealForest },
          { SeasonalForest },
          { SeasonalForest },
          { SeasonalForest },
          { TropicalForest, Savanna },
          { TropicalForest, Savanna },
          { TropicalForest, Savanna },
          { TropicalForest, Savanna },
        },
        {
          { Ice },
          { Tundra },
          { BorealForest },
          { SeasonalForest },
          { SeasonalForest },
          { SeasonalForest },
          { TropicalRainforest },
          { TropicalRainforest },
          { TropicalRainforest },
          { TropicalForest, Savanna },
        },
        {
          { Ice },
          { Tundra },
          { BorealForest },
          { TemperateRainforest },
          { SeasonalForest },
          { SeasonalForest },
          { TropicalRainforest },
          { TropicalRainforest },
          { TropicalRainforest },
          { TropicalRainforest },
        },
        {
          { Ice },
          { Tundra },
          { BorealForest },
          { TemperateRainforest },
          { TemperateRainforest },
          { TemperateRainforest },
          { TropicalRainforest },
          { TropicalRainforest },
          { TropicalRainforest },
          { TropicalRainforest },
        },
    };
}
