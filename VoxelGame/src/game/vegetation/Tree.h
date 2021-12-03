#pragma once
#include <vector>

#include "engine/GameObject.h"
#include "game/Terrain.h"

namespace Terrain::Vegetation {
class Tree {
  public:
    static std::vector<GameObject> SpawnNormalTree(const glm::vec3& pos);
    static std::vector<GameObject> SpawnJungleTree(const glm::vec3& pos, float height = 6.0f, float heightVar = 3.0f);
    static std::vector<GameObject> SpawnSavannaTree(const glm::vec3& pos, float height = 2.0f, float heightVar = 2.0f);
    static std::vector<GameObject> SpawnCactus(const glm::vec3& pos);
    static std::vector<GameObject> SpawnShrub(const glm::vec3& pos);

    static std::vector<glm::mat4> SpawnLSystemNormalTree(const glm::vec3& pos);
    static std::vector<glm::mat4> SpawnLSystemJungleTree(const glm::vec3& pos);
    static std::vector<glm::mat4> SpawnLSystemSavannaTree(const glm::vec3& pos);
    static std::vector<glm::mat4> SpawnLSystemShrub(const glm::vec3& pos);

    // TODO: use L-systems for this
    static std::vector<glm::mat4> SpawnLSystemCactus(const glm::vec3& pos);

  private:
    static std::vector<GameObject> GenerateTree(const std::vector<std::pair<glm::vec3, BlockType>>& tree);
    static float GetTreeHeight(const glm::vec3& pos, float height, float heightVar);

    static std::vector<glm::mat4> GenerateObjectData(const std::vector<GameObject>& objects);
};

} // namespace Terrain::Vegetation
