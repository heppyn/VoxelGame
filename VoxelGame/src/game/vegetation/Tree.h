#pragma once
#include <vector>

#include "engine/GameObject.h"

namespace Terrain::Vegetation {
class Tree {

  public:
    static std::vector<GameObject> SpawnTree(const glm::vec3& pos);
};

} // namespace Terrain::Vegetation
