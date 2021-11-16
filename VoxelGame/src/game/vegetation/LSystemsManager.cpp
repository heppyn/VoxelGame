#include "LSystemsManager.h"

#include "engine/Components/Transform.h"
#include "engine/Components/SpritesheetTex.h"
#include "engine/L-systems/LSystemParser.h"
#include "engine/L-systems/LSystemExecutor.h"
#include "helpers/Math.h"

std::vector<Terrain::Vegetation::Detail::PlantModel> Terrain::Vegetation::LSystemsManager::Shrubs_{};


size_t Terrain::Vegetation::Detail::PlantModel::Size() const {
    size_t modelSize = 0;
    for (const auto& plantPart : Model) {
        modelSize += plantPart.size();
    }

    return modelSize;
}

void Terrain::Vegetation::LSystemsManager::Init() {
    const auto lSystems = LSystems::LSystemParser::LoadLSystemFromFile(SHRUB_PATH);
    assert(!lSystems.empty());
    LSystems::LSystemExecutor executor;
    auto salt = Engine::Random::Get1dNoise(Engine::Random::Seed);

    for (const auto& ls : lSystems) {
        for (int i = 0; i < SHRUB_COUNT; ++i) {
            // add different grow stages
            // larger plants have thicker stems
            const auto mod = i % 3;
            const auto tmpObjects = executor.GenerateBasedOn(glm::vec3(0.0f), ls, 0.1f + mod / 20.0f, 2 + mod, salt);
            Shrubs_.emplace_back();

            for (const auto& plantPart : tmpObjects) {
                auto& plantModel = Shrubs_[Shrubs_.size() - 1].Model;
                plantModel.emplace_back();
                plantModel[plantModel.size() - 1].reserve(plantPart.size());

                for (const auto& o : plantPart) {
                    assert(o.HasComponent<Components::Transform>());
                    plantModel[plantModel.size() - 1].emplace_back(o.GetComponent<Components::Transform>().ModelMat());
                }
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
    const auto& plantModel = Shrubs_[index];
    res.reserve(plantModel.Size());
    const auto texPos = Components::SpritesheetTex(GetTextPos(blockType)).GetTexPos();

    for (const auto& plantPart : plantModel.Model) {
        for (const auto& m : plantPart) {
            // objects may be scaled
            // move by unscaled coords
            auto model = glm::translate(m, { pos.x / m[0][0], pos.y / m[1][1], pos.z / m[1][1] });
            Helpers::Math::PackVecToMatrix(model, texPos);
            res.emplace_back(model);
        }
    }

    return res;
}
