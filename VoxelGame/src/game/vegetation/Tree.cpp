#include "Tree.h"

#include "engine/Random.h"
#include "game/BlockFactory.h"

std::vector<GameObject> Terrain::Vegetation::Tree::SpawnNormalTree(const glm::vec3& pos) {
    // don't use copy constructor of GameObject
    const std::vector<std::pair<glm::vec3, BlockType>> tree{
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

    return GenerateTree(tree);
}

std::vector<GameObject> Terrain::Vegetation::Tree::SpawnJungleTree(const glm::vec3& pos, float height/* = 6.0f*/, float height_var/* = 3.0f*/) {
    const auto treeHeight = Engine::Random::Get3dNoise0_1<float>(pos.x, pos.y, pos.z) * height_var + height;
    std::vector tree {
        std::make_pair(glm::vec3(pos.x, pos.y + treeHeight, pos.z), BlockType::Leaves),
        std::make_pair(glm::vec3(pos.x + 1.0f, pos.y + treeHeight - 1.0f, pos.z), BlockType::Leaves),
        std::make_pair(glm::vec3(pos.x - 1.0f, pos.y + treeHeight - 1.0f, pos.z), BlockType::Leaves),
        std::make_pair(glm::vec3(pos.x, pos.y + treeHeight - 1.0f, pos.z + 1.0f), BlockType::Leaves),
        std::make_pair(glm::vec3(pos.x, pos.y + treeHeight - 1.0f, pos.z - 1.0f), BlockType::Leaves),
    };

    for (auto i = 1; i < static_cast<int>(treeHeight); ++i) {
        tree.emplace_back(std::make_pair(glm::vec3(pos.x, pos.y + static_cast<float>(i), pos.z), BlockType::TrunkSide));
    }

    return GenerateTree(tree);
}

std::vector<GameObject> Terrain::Vegetation::Tree::GenerateTree(const std::vector<std::pair<glm::vec3, BlockType>>& tree) {
    std::vector<GameObject> res;
    res.reserve(tree.size());
    for (const auto& [pos, type] : tree) {
        res.emplace_back(BlockFactory::CreateBlock(pos, type));
    }

    return res;
}
