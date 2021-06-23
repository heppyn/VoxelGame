#pragma once

#include "engine/Chunk.h"
#include "glm/vec2.hpp"
#include "engine/GameObject.h"

namespace Terrain {
class TerrainGen {
  public:
    static ::Chunk GenerateChunk(const glm::vec2& position);
};
} // namespace Terrain
