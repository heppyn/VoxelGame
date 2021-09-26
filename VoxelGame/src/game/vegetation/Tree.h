#pragma once
#include <vector>

#include "engine/GameObject.h"
#include "game/Terrain.h"

namespace Terrain::Vegetation {
class Tree {

  public:
    static std::vector<GameObject> SpawnNormalTree(const glm::vec3& pos);
    static std::vector<GameObject> SpawnJungleTree(const glm::vec3& pos, float height = 6.0f, float height_var = 3.0f);

private:
    static std::vector<GameObject> GenerateTree(const std::vector<std::pair<glm::vec3, BlockType>>& tree);
};

} // namespace Terrain::Vegetation
