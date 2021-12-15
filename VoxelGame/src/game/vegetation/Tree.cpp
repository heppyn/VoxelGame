#include "Tree.h"

#include "engine/Random.h"
#include "engine/Components/SpritesheetTex.h"
#include "engine/Components/Transform.h"
#include "game/BlockFactory.h"
#include "game/vegetation/LSystemsManager.h"
#include "helpers/Math.h"

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
        std::make_pair(glm::vec3(curPos.x, curPos.y + 1.0f, curPos.z), BlockType::LeavesOrange),
        std::make_pair(glm::vec3(curPos.x + 1.0f, curPos.y, curPos.z), BlockType::LeavesOrange),
        std::make_pair(glm::vec3(curPos.x - 1.0f, curPos.y, curPos.z), BlockType::LeavesOrange),
        std::make_pair(glm::vec3(curPos.x, curPos.y, curPos.z + 1.0f), BlockType::LeavesOrange),
        std::make_pair(glm::vec3(curPos.x, curPos.y, curPos.z - 1.0f), BlockType::LeavesOrange),
      });

    return GenerateTree(tree);
}

std::vector<GameObject> Terrain::Vegetation::Tree::SpawnCactus(const glm::vec3& pos) {
    const std::vector cactus = {
        std::make_pair(glm::vec3(pos.x, pos.y + 1.0f, pos.z), BlockType::CactusSide),
        std::make_pair(glm::vec3(pos.x, pos.y + 2.0f, pos.z), BlockType::CactusSide),
        std::make_pair(glm::vec3(pos.x, pos.y + 3.0f, pos.z), BlockType::CactusSide),
    };

    std::vector<GameObject> res;
    res.reserve(cactus.size());
    BlockFactory bf(glm::vec3(0.8f), glm::vec3(0.0f, -0.1f, 0.0f));

    for (const auto& [position, type] : cactus) {
        res.emplace_back(bf.CreateStacked(position, type));
    }

    return res;
}

std::vector<GameObject> Terrain::Vegetation::Tree::SpawnShrub(const glm::vec3& pos) {
    std::vector<GameObject> res;
    const auto scale = Engine::Random::Get2dNoise0_1<float>(pos.x, pos.z) * 0.5f + 0.5f;
    BlockFactory bf(glm::vec3(scale), glm::vec3(0.0f, (1.0f - scale) / -2.0f, 0.0f));
    res.emplace_back(bf.CreateFromPreset(pos + glm::vec3(0.0f, 1.0f, 0.0f), BlockType::LeavesOrange));
    return res;
}

std::vector<glm::mat4> Terrain::Vegetation::Tree::SpawnLSystemShrub(const glm::vec3& pos) {
    return GenerateObjectData(SpawnShrub(pos));

    //return LSystemsManager::GetShrub({ pos.x, pos.y + 1.0f, pos.z }, { BlockType::TrunkSide, BlockType::Leaves });
}

std::vector<glm::mat4> Terrain::Vegetation::Tree::SpawnLSystemNormalTree(const glm::vec3& pos) {
    return GenerateObjectData(SpawnNormalTree(pos));

    //const auto oak = Engine::Random::GetNoise0_1<float>(pos) > 0.3f;
    //const auto trunk = oak ? BlockType::TrunkSide : BlockType::TrunkWhiteSide;
    //const auto leaves = oak ? BlockType::Leaves : BlockType::Leaves2;
    //return LSystemsManager::GetNormalTree({ pos.x, pos.y + 1.0f, pos.z }, trunk, leaves);
}
std::vector<glm::mat4> Terrain::Vegetation::Tree::SpawnLSystemJungleTree(const glm::vec3& pos) {
    return GenerateObjectData(SpawnJungleTree(pos));

    //const auto baobab = Engine::Random::GetNoise0_1<float>(pos) > 0.7f;
    //const auto trunk = baobab ? BlockType::TrunkOrangeSide : BlockType::TrunkSide;

    //return LSystemsManager::GetJungleTree({ pos.x, pos.y + 1.0f, pos.z }, trunk, BlockType::Leaves2, baobab ? 1 : 0);
}
std::vector<glm::mat4> Terrain::Vegetation::Tree::SpawnLSystemSavannaTree(const glm::vec3& pos) {
    return GenerateObjectData(SpawnSavannaTree(pos));
    //return LSystemsManager::GetAcacia({ pos.x, pos.y + 1.0f, pos.z }, BlockType::TrunkOrangeSide, BlockType::LeavesOrange);
}
std::vector<glm::mat4> Terrain::Vegetation::Tree::SpawnLSystemCactus(const glm::vec3& pos) {
    return GenerateObjectData(SpawnCactus(pos));
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

std::vector<glm::mat4> Terrain::Vegetation::Tree::GenerateObjectData(const std::vector<GameObject>& objects) {
    std::vector<glm::mat4> res;

    // TODO: implement in common function
    for (const auto& o : objects) {
        assert(o.HasComponent<Components::Transform>());
        auto model = o.GetComponent<Components::Transform>().ModelMat();

        assert(o.HasComponent<Components::SpritesheetTex>());
        const auto& texPos = o.GetComponent<Components::SpritesheetTex>().GetTexPos();
        Helpers::Math::PackVecToMatrix(model, texPos);

        res.push_back(model);
    }

    return res;
}
