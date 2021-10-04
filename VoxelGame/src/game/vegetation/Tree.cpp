#include "Tree.h"

#include "engine/Random.h"
#include "game/BlockFactory.h"

std::vector<GameObject> Terrain::Vegetation::Tree::SpawnNormalTree(const glm::vec3& pos) {
    const auto trunk = Engine::Random::GetNoise0_1<float>(pos) > 0.3f ? BlockType::TrunkSide : BlockType::TrunkWhiteSide;

    // don't use copy constructor of GameObject
    const std::vector<std::pair<glm::vec3, BlockType>> tree{
        std::make_pair(glm::vec3(pos.x, pos.y + 1.0f, pos.z), trunk),
        std::make_pair(glm::vec3(pos.x, pos.y + 2.0f, pos.z), trunk),
        std::make_pair(glm::vec3(pos.x, pos.y + 3.0f, pos.z), trunk),

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

std::vector<GameObject> Terrain::Vegetation::Tree::SpawnJungleTree(const glm::vec3& pos, float height /* = 6.0f*/, float heightVar /* = 3.0f*/) {
    const auto treeHeight = GetTreeHeight(pos, height, heightVar);
    std::vector tree{
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

std::vector<GameObject> Terrain::Vegetation::Tree::SpawnSavannaTree(const glm::vec3& pos, float height, float heightVar) {
    const auto treeHeight = GetTreeHeight(pos, height, heightVar);
    std::vector<std::pair<glm::vec3, BlockType>> tree;

    auto curPos = glm::vec3(pos.x, pos.y + 1.0f, pos.z);
    tree.emplace_back(std::make_pair(curPos, BlockType::TrunkOrangeSide));

    for (auto i = 1; i < static_cast<int>(treeHeight); ++i) {
        const auto rx = std::round(Engine::Random::Get2dNoise0_1<float>(curPos.x, curPos.z) * 2.0f - 1.0f);
        const auto rz = std::round(Engine::Random::Get2dNoise0_1<float>(curPos.z, curPos.x) * 2.0f - 1.0f);

        curPos += glm::vec3(rx, 1.0f, rz);
        tree.emplace_back(std::make_pair(curPos, BlockType::TrunkOrangeSide));
    }

    curPos += glm::vec3(0.0f, 1.0f, 0.0f);
    tree.insert(tree.end(), 
    {
        std::make_pair(glm::vec3(curPos.x, curPos.y, curPos.z), BlockType::TrunkOrangeSide),
        std::make_pair(glm::vec3(curPos.x, curPos.y + 1.0f, curPos.z), BlockType::Leaves),
        std::make_pair(glm::vec3(curPos.x + 1.0f, curPos.y, curPos.z), BlockType::Leaves),
        std::make_pair(glm::vec3(curPos.x - 1.0f, curPos.y, curPos.z), BlockType::Leaves),
        std::make_pair(glm::vec3(curPos.x, curPos.y, curPos.z + 1.0f), BlockType::Leaves),
        std::make_pair(glm::vec3(curPos.x, curPos.y, curPos.z - 1.0f), BlockType::Leaves),
    });

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

float Terrain::Vegetation::Tree::GetTreeHeight(const glm::vec3& pos, float height, float heightVar) {
    return Engine::Random::GetNoise0_1<float>(pos) * heightVar + height;
}
