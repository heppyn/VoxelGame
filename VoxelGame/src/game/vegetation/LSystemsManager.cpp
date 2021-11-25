#include "LSystemsManager.h"

#include "engine/Components/Transform.h"
#include "engine/Components/SpritesheetTex.h"
#include "engine/L-systems/LSystemParser.h"
#include "engine/L-systems/LSystemExecutor.h"
#include "helpers/Math.h"

std::vector<Terrain::Vegetation::Detail::PlantModel> Terrain::Vegetation::LSystemsManager::Shrubs_{};
std::vector<LSystems::LSystem> Terrain::Vegetation::LSystemsManager::AcaciaLSystems_{};


Terrain::Vegetation::Detail::PlantModel::PlantModel(const std::vector<std::vector<GameObject>>& gameObjects) {
    for (const auto& plantPart : gameObjects) {
        Model.emplace_back();
        Model[Model.size() - 1].reserve(plantPart.size());

        for (const auto& o : plantPart) {
            assert(o.HasComponent<Components::Transform>());
            Model[Model.size() - 1].emplace_back(o.GetComponent<Components::Transform>().ModelMat());
        }
    }
}

size_t Terrain::Vegetation::Detail::PlantModel::Size() const {
    size_t modelSize = 0;
    for (const auto& plantPart : Model) {
        modelSize += plantPart.size();
    }

    return modelSize;
}

void Terrain::Vegetation::LSystemsManager::Init() {
    AcaciaLSystems_ = LSystems::LSystemParser::LoadLSystemFromFile(ACACIA_PATH);
    assert(!AcaciaLSystems_.empty());

    // prepare cached shrubs
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
            Shrubs_.emplace_back(tmpObjects);

            salt = Engine::Random::Get1dNoise(salt);
        }
    }
    assert(!Shrubs_.empty());
}

void Terrain::Vegetation::LSystemsManager::Clear() {
    Shrubs_.clear();
    AcaciaLSystems_.clear();
}

std::vector<glm::mat4> Terrain::Vegetation::LSystemsManager::GetShrub(const glm::vec3& pos, BlockType blockType) {
    return GetShrub(pos, std::vector(1, blockType));
}

// TODO: get rid of the vector, use template
std::vector<glm::mat4> Terrain::Vegetation::LSystemsManager::GetShrub(const glm::vec3& pos, const std::vector<BlockType>& blockTypes) {
    assert(!Shrubs_.empty());
    const auto index = Engine::Random::GetNoiseLimited(pos, Shrubs_.size());

    return GetPlant(pos, Shrubs_[index], blockTypes);
}

std::vector<glm::mat4> Terrain::Vegetation::LSystemsManager::GetAcacia(const glm::vec3& pos, BlockType trunk, BlockType leaves) {
    LSystems::LSystemExecutor executor(0.15f);
    const auto newPos = glm::vec3(pos.x, pos.y + 1, pos.z);

    const auto salt = Engine::Random::GetNoise(newPos);
    const auto acacia = executor.GenerateBasedOn(newPos, AcaciaLSystems_[0], 1.0f, 4, salt, false);

    return GetPlant(Detail::PlantModel(acacia), { trunk, leaves });
}

std::vector<glm::mat4> Terrain::Vegetation::LSystemsManager::GetPlant(const glm::vec3& pos, const Detail::PlantModel& plantModel, const std::vector<BlockType>& blockTypes) {
    std::vector<glm::mat4> res;
    res.reserve(plantModel.Size());
    size_t blockTypeIndex = 0;

    for (const auto& plantPart : plantModel.Model) {
        const auto texPos = Components::SpritesheetTex(GetTextPos(blockTypes[blockTypeIndex])).GetTexPos();
        for (const auto& m : plantPart) {
            // objects may be scaled
            // move by unscaled coords
            auto model = glm::translate(m, { pos.x / m[0][0], pos.y / m[1][1], pos.z / m[2][2] });
            Helpers::Math::PackVecToMatrix(model, texPos);
            res.emplace_back(model);
        }
        // change texture when one is present
        blockTypeIndex += blockTypeIndex >= blockTypes.size() - 1 ? 0 : 1;
    }

    return res;
}

std::vector<glm::mat4> Terrain::Vegetation::LSystemsManager::GetPlant(const Detail::PlantModel& plantModel, const std::vector<BlockType>& blockTypes) {
    // TODO: get rid of the position
    return GetPlant(glm::vec3(0.0f), plantModel, blockTypes);
}
