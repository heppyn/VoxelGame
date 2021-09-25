#include "Tree.h"

#include "game/Terrain.h"
#include "game/BlockFactory.h"

std::vector<GameObject> Terrain::Vegetation::Tree::SpawnTree(const glm::vec3& pos) {
    // don't use copy constructor of GameObject
    std::vector<std::pair<glm::vec3, BlockType>> tree{
        std::make_pair(glm::vec3(pos.x, pos.y + 1.0f, pos.z), BlockType::TrunkSide),
        std::make_pair(glm::vec3(pos.x, pos.y + 2.0f, pos.z), BlockType::TrunkSide),
        std::make_pair(glm::vec3(pos.x, pos.y + 3.0f, pos.z), BlockType::TrunkSide),

        std::make_pair(glm::vec3(pos.x, pos.y + 6.0f, pos.z), BlockType::Leaves),

        std::make_pair(glm::vec3(pos.x + 1.0f, pos.y + 4.0f, pos.z), BlockType::Leaves),
        std::make_pair(glm::vec3(pos.x - 1.0f, pos.y + 4.0f, pos.z), BlockType::Leaves),
        std::make_pair(glm::vec3(pos.x, pos.y + 4.0f, pos.z + 1.0f), BlockType::Leaves),
        std::make_pair(glm::vec3(pos.x, pos.y + 4.0f, pos.z - 1.0f), BlockType::Leaves),
        std::make_pair(glm::vec3(pos.x + 1.0f, pos.y + 5.0f, pos.z), BlockType::Leaves),
        std::make_pair(glm::vec3(pos.x - 1.0f, pos.y + 5.0f, pos.z), BlockType::Leaves),
        std::make_pair(glm::vec3(pos.x, pos.y + 5.0f, pos.z + 1.0f), BlockType::Leaves),
        std::make_pair(glm::vec3(pos.x, pos.y + 5.0f, pos.z - 1.0f), BlockType::Leaves),
    };

    std::vector<GameObject> res;
    res.reserve(tree.size());
    for (const auto& [pos, type] : tree) {
        res.emplace_back(BlockFactory::CreateBlock(pos, type));
    }

    return res;
}
