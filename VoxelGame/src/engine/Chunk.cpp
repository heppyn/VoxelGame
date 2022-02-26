#include "Chunk.h"

#include <iostream>
#include <array>
#include <algorithm>
#include <ranges>

#include "Components/SpritesheetTex.h"
#include "Components/Transform.h"
#include "helpers/Math.h"

float Chunk::ChunkSize{ 16.0f };

Chunk::Chunk(const glm::vec2& position)
  : Position(position)
  , BlockInfos_(static_cast<size_t>(ChunkSize), std::vector(static_cast<size_t>(ChunkSize), BlockInfo()))
  , PositionInSpace_(position.x, 0.0f, position.y) {
    InstancesData_[DefaultCube_] = std::make_shared<std::vector<glm::mat4>>();
}

Chunk::Chunk(const glm::vec2& position, std::vector<GameObject>&& objects)
  : Position(position)
  , BlockInfos_(static_cast<size_t>(ChunkSize), std::vector(static_cast<size_t>(ChunkSize), BlockInfo()))
  , PositionInSpace_(position.x, 0.0f, position.y) {
    Objects_[DefaultCube_] = std::move(objects);
    InstancesData_[DefaultCube_] = std::make_shared<std::vector<glm::mat4>>();
    GenerateInstanceData();
    // not used now
    //RecalculateBlockHeights();
}

void Chunk::GenerateInstanceData() {
    GenerateInstanceData(Objects_, InstancesData_);
    GenerateInstanceData(ObjectsTrans_, InstancesDataTrans_);
}

void Chunk::FinisChunk() {
    for (auto& objects : Objects_ | std::views::values) {
        objects.shrink_to_fit();
    }
    for (auto& objects : ObjectsTrans_ | std::views::values) {
        objects.shrink_to_fit();
    }
    GenerateInstanceData();
    SetPositionInSpace();
}

// don't make const because data in pointer are changed
void Chunk::AddObjectData(std::vector<glm::mat4>&& objects) {
    // TODO: choose cube, if so create shared ptr
    InstancesData_[DefaultCube_]->insert(
      InstancesData_[DefaultCube_]->end(),
      std::make_move_iterator(objects.begin()),
      std::make_move_iterator(objects.end()));
}

void Chunk::AddObject(GameObject&& object, Engine::Cube::BlockFaces faces) {
    Objects_[faces].emplace_back(std::move(object));
}
void Chunk::AddObjectTrans(GameObject&& object, Engine::Cube::BlockFaces faces) {
    ObjectsTrans_[faces].emplace_back(std::move(object));
}

void Chunk::AddObjects(std::vector<GameObject>&& objects, Engine::Cube::BlockFaces faces) {
    Objects_[faces].insert(
      Objects_[faces].end(),
      std::make_move_iterator(objects.begin()),
      std::make_move_iterator(objects.end()));
}
void Chunk::AddObjectsTrans(std::vector<GameObject>&& objects, Engine::Cube::BlockFaces faces) {
    ObjectsTrans_[faces].insert(
      ObjectsTrans_[faces].end(),
      std::make_move_iterator(objects.begin()),
      std::make_move_iterator(objects.end()));
}

const std::map<Engine::Cube::BlockFaces, std::shared_ptr<std::vector<glm::mat4>>>& Chunk::GetInstancesData() const {
    assert(!InstancesData_.at(DefaultCube_)->empty());

    return InstancesData_;
}

std::map<Engine::Cube::BlockFaces, std::shared_ptr<std::vector<glm::mat4>>>& Chunk::GetInstancesData() {
    return InstancesData_;
}

const std::map<Engine::Cube::BlockFaces, std::vector<GameObject>>& Chunk::GetObjects() const {
    return Objects_;
}

std::map<Engine::Cube::BlockFaces, std::vector<GameObject>>& Chunk::GetObjects() {
    return Objects_;
}

std::map<Engine::Cube::BlockFaces, std::shared_ptr<std::vector<glm::mat4>>>& Chunk::GetInstancesDataTrans() {
    // can be empty if no transparent textures are present in the chunk
    return InstancesDataTrans_;
}

const std::map<Engine::Cube::BlockFaces, std::shared_ptr<std::vector<glm::mat4>>>& Chunk::GetInstancesDataTrans() const {
    // can be empty if no transparent textures are present in the chunk
    return InstancesDataTrans_;
}

const std::map<Engine::Cube::BlockFaces, std::vector<GameObject>>& Chunk::GetObjectsTrans() const {
    return ObjectsTrans_;
}

std::map<Engine::Cube::BlockFaces, std::vector<GameObject>>& Chunk::GetObjectsTrans() {
    return ObjectsTrans_;
}

BlockInfo& Chunk::GetBlockInfo(const glm::vec2& pos) {
    const auto x = static_cast<unsigned>(pos.x - Position.x);
    const auto y = static_cast<unsigned>(pos.y - Position.y);
    return BlockInfos_[y][x];
}

BlockInfo& Chunk::GetBlockInfo(const glm::vec3& pos) {
    return GetBlockInfo({ pos.x, pos.z });
}

void Chunk::RecalculateBlockHeights() {
    std::cout << "Warning! Using expansive function\n";

    for (auto& vec : BlockInfos_) {
        for (auto& info : vec) {
            info.SetSurfaceHeight(0.0f);
        }
    }

    for (const auto& o : Objects_[DefaultCube_]) {
        GetBlockInfo(o.Position()).SetSurfaceHeight(std::max(GetBlockInfo(o.Position()).GetSurfaceHeight(), o.Position().y));
    }
}

void Chunk::GenerateInstanceData(
  const std::map<Engine::Cube::BlockFaces, std::vector<GameObject>>& objects,
  std::map<Engine::Cube::BlockFaces, std::shared_ptr<std::vector<glm::mat4>>>& buffer) {
    for (auto& [cube, obs] : objects) {
        if (!buffer.contains(cube)) {
            buffer[cube] = std::make_shared<std::vector<glm::mat4>>();
        }
        // don't clear if objects data were added
        // chunks are not regenerated
        buffer[cube]->reserve(buffer[cube]->size() + objects.size());

        for (const auto& o : obs) {
            assert(o.HasComponent<Components::Transform>());
            auto model = o.GetComponent<Components::Transform>().ModelMat();

            assert(o.HasComponent<Components::SpritesheetTex>());
            const auto& texPos = o.GetComponent<Components::SpritesheetTex>().GetTexPos();
            Helpers::Math::PackVecToMatrix(model, texPos);

            buffer[cube]->push_back(model);
        }
    }
}

void Chunk::SetPositionInSpace() {
    assert(!BlockInfos_.empty() && !BlockInfos_.at(0).empty());

    const auto last = static_cast<size_t>(ChunkSize) - 1;
    const float minHeight = std::ranges::min(
      { BlockInfos_[0][0].GetSurfaceHeight(),
        BlockInfos_[0][last].GetSurfaceHeight(),
        BlockInfos_[last][0].GetSurfaceHeight(),
        BlockInfos_[last][last].GetSurfaceHeight() });

    PositionInSpace_ = { Position.x, minHeight, Position.y };
}
