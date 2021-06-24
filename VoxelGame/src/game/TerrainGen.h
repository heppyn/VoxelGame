#pragma once

#include <random>

#include "engine/Chunk.h"
#include "glm/vec2.hpp"

namespace Terrain {
class TerrainGen {
  public:
    static ::Chunk GenerateChunk(const glm::vec2& position);

  private:
    static unsigned Seed_;
    static std::random_device Random_;
};
} // namespace Terrain
