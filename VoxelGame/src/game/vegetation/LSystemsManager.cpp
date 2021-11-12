#include "LSystemsManager.h"

#include "engine/Components/Transform.h"
#include "engine/Components/SpritesheetTex.h"
#include "engine/L-systems/LSystemParser.h"
#include "engine/L-systems/LSystemExecutor.h"
#include "helpers/Math.h"

std::vector<std::vector<glm::mat4>> Terrain::Vegetation::LSystemsManager::Shrubs_{};


void Terrain::Vegetation::LSystemsManager::Init() {
    const auto lSystems = LSystems::LSystemParser::LoadLSystemFromFile(SHRUB_PATH);
    assert(!lSystems.empty());
    auto executor = LSystems::LSystemExecutor(2);
    auto salt = Engine::Random::Get1dNoise(Engine::Random::Seed);

    for (const auto& ls : lSystems) {
        for (int i = 0; i < SHRUB_COUNT; ++i) {
            const auto tmpObjects = executor.GenerateBasedOn(glm::vec3(0.0f), ls, 0.1f, 2, salt);
            Shrubs_.emplace_back();
            Shrubs_[Shrubs_.size() - 1].reserve(tmpObjects.size());

            for (const auto& o : tmpObjects) {
                assert(o.HasComponent<Components::Transform>());
                Shrubs_[Shrubs_.size() - 1].emplace_back(o.GetComponent<Components::Transform>().ModelMat());
            }
            salt = Engine::Random::Get1dNoise(salt);
        }
    }
    assert(!Shrubs_.empty());
}

void Terrain::Vegetation::LSystemsManager::Clear() {
    Shrubs_.clear();
}

std::vector<glm::mat4> Terrain::Vegetation::LSystemsManager::GetShrub(const glm::vec3& pos, BlockType blockType) {
    assert(!Shrubs_.empty());
    const auto index = Engine::Random::GetNoiseLimited(pos, Shrubs_.size());
    std::vector<glm::mat4> res;
    res.reserve(Shrubs_[index].size());
    const auto texPos = Components::SpritesheetTex(GetTextPos(blockType)).GetTexPos();

    for (const auto& m : Shrubs_[index]) {
        // objects may be scaled
        // move by unscaled coords
        auto model = glm::translate(m, { pos.x / m[0][0], pos.y / m[1][1], pos.z / m[1][1] });
        Helpers::Math::PackVecToMatrix(model, texPos);
        res.emplace_back(model);
    }

    return res;
}
