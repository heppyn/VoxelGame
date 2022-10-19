#pragma once

#include <engine/Chunk.h>

class ExampleScene {
  public:
    [[nodiscard]] static Chunk EmptySides(const glm::vec2&);
    [[nodiscard]] static Chunk FaceCullingGrass(const glm::vec2&);
    [[nodiscard]] static Chunk AlphaBlendingGrass(const glm::vec2&);
    [[nodiscard]] static Chunk LSystemGrass(const glm::vec2&);
    [[nodiscard]] static Chunk LSystemTrees(const glm::vec2&);
    [[nodiscard]] static Chunk PhongLight(const glm::vec2&);
    [[nodiscard]] static Chunk Shadow(const glm::vec2&);
    [[nodiscard]] static Chunk RandomNoiseTerrain(const glm::vec2&);
    [[nodiscard]] static Chunk PerlinSimplexTerrain(const glm::vec2&);
    [[nodiscard]] static Chunk TreeDistribution(const glm::vec2&);
};
