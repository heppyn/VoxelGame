#include "Biome.h"

#include <cassert>

#include "engine/Chunk.h"
#include "engine/Random.h"

float Terrain::Biome::Frequency_{ 10.0f };
std::vector<std::vector<std::vector<Terrain::BiomeType>>> Terrain::Biome::BiomeTable_{};

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
