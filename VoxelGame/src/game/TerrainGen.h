#pragma once
#include <vector>

#include "glm/vec2.hpp"
#include "engine/GameObject.h"


namespace Terrain {
class TerrainGen {
  private:
    inline static unsigned int ChunkSize{ 16 };

  public:
    static std::vector<GameObject> GenerateChunk(const glm::vec2& position);

    [[nodiscard]] static unsigned int GetChunkSize() { return ChunkSize; }
};
} // namespace Terrain
