#pragma once

#include "engine/Chunk.h"

class ExampleScene {
  public:
    [[nodiscard]] static Chunk EmptySides();
    [[nodiscard]] static Chunk FaceCullingGrass();
    [[nodiscard]] static Chunk AlphaBlendingGrass();
    [[nodiscard]] static Chunk LSystemGrass();
    [[nodiscard]] static Chunk PhongLight();
    [[nodiscard]] static Chunk Shadow();
    [[nodiscard]] static Chunk RandomNoiseTerrain();
    [[nodiscard]] static Chunk PerlinSimplexTerrain();
    [[nodiscard]] static Chunk TreeDistribution();
};
