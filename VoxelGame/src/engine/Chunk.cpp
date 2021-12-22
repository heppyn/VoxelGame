#include "Chunk.h"

#include <iostream>

#include "Components/SpritesheetTex.h"
#include "Components/Transform.h"
#include "helpers/Math.h"

float Chunk::ChunkSize{ 16.0f };

Chunk::Chunk(const glm::vec2& position)
  : Position(position), BlockInfos_(static_cast<size_t>(ChunkSize), std::vector(static_cast<size_t>(ChunkSize), BlockInfo())) {
    InstancesData_ = std::make_shared<std::vector<glm::mat4>>();
    InstancesDataTrans_ = std::make_shared<std::vector<glm::mat4>>();
}

Chunk::Chunk(const glm::vec2& position, std::vector<GameObject>&& objects)
  : Position(position), Objects_(std::move(objects)), BlockInfos_(static_cast<size_t>(ChunkSize), std::vector(static_cast<size_t>(ChunkSize), BlockInfo())) {
    InstancesData_ = std::make_shared<std::vector<glm::mat4>>();
    InstancesDataTrans_ = std::make_shared<std::vector<glm::mat4>>();
    GenerateInstanceData();
    // not used now
    //RecalculateBlockHeights();
}

void Chunk::GenerateInstanceData() {
    GenerateInstanceData(Objects_, InstancesData_);
    GenerateInstanceData(ObjectsTrans_, InstancesDataTrans_);
}

void Chunk::FinisChunk() {
    Objects_.shrink_to_fit();
    ObjectsTrans_.shrink_to_fit();
    GenerateInstanceData();
}

// don't make const because data in pointer are changed
void Chunk::AddObjectData(std::vector<glm::mat4>&& objects) {
    InstancesData_->insert(
      InstancesData_->end(),
      std::make_move_iterator(objects.begin()),
      std::make_move_iterator(objects.end()));
}

std::shared_ptr<std::vector<glm::mat4>> Chunk::GetInstancesData() const {
    assert(!InstancesData_->empty());

    return InstancesData_;
}

const std::vector<GameObject>& Chunk::GetObjects() const {
    return Objects_;
}

std::vector<GameObject>& Chunk::GetObjects() {
    return Objects_;
}

std::shared_ptr<std::vector<glm::mat4>> Chunk::GetInstancesDataTrans() const {
    // can be empty if no transparent textures are present in the chunk
    return InstancesDataTrans_;
}

const std::vector<GameObject>& Chunk::GetObjectsTrans() const {
    return ObjectsTrans_;
}

std::vector<GameObject>& Chunk::GetObjectsTrans() {
    return ObjectsTrans_;
}

BlockInfo& Chunk::GetBlockInfo(const glm::vec2& pos) {
    const auto x = static_cast<unsigned>(std::abs(pos.x)) % static_cast<unsigned>(ChunkSize);
    const auto y = static_cast<unsigned>(std::abs(pos.y)) % static_cast<unsigned>(ChunkSize);
    return BlockInfos_[x][y];
}

BlockInfo& Chunk::GetBlockInfo(const glm::vec3& pos) {
    return GetBlockInfo({ pos.x, pos.y });
}

void Chunk::RecalculateBlockHeights() {
    std::cout << "Warning! Using expansive function\n";

    for (auto& vec : BlockInfos_) {
        for (auto& info : vec) {
            info.SetSurfaceHeight(0.0f);
        }
    }

    for (const auto& o : Objects_) {
        const auto& pos = o.Position();
        const auto x = static_cast<int>(pos.x);
        const auto y = static_cast<int>(pos.z);
        BlockInfos_[x][y].SetSurfaceHeight(std::max(BlockInfos_[x][y].GetSurfaceHeight(), pos.y));
    }
}

void Chunk::GenerateInstanceData(const std::vector<GameObject>& objects, std::shared_ptr<std::vector<glm::mat4>> buffer) {
    // don't clear if objects data were added
    // chunks are not regenerated
    buffer->reserve(buffer->size() + objects.size());

    for (const auto& o : objects) {
        assert(o.HasComponent<Components::Transform>());
        auto model = o.GetComponent<Components::Transform>().ModelMat();

        assert(o.HasComponent<Components::SpritesheetTex>());
        const auto& texPos = o.GetComponent<Components::SpritesheetTex>().GetTexPos();
        Helpers::Math::PackVecToMatrix(model, texPos);

        buffer->push_back(model);
    }
}
