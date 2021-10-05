#include "Chunk.h"

#include <iostream>

#include "Components/SpritesheetTex.h"
#include "helpers/Math.h"

float Chunk::ChunkSize{ 16.0f };

Chunk::Chunk(const glm::vec2& position)
  : Position(position), BlockInfos_(static_cast<size_t>(ChunkSize), std::vector(static_cast<size_t>(ChunkSize), BlockInfo())) {
    InstancesData_ = std::make_shared<std::vector<glm::mat4>>();
}

Chunk::Chunk(const glm::vec2& position, std::vector<GameObject>&& objects)
  : Position(position), Objects_(std::move(objects)), BlockInfos_(static_cast<size_t>(ChunkSize), std::vector(static_cast<size_t>(ChunkSize), BlockInfo())) {
    InstancesData_ = std::make_shared<std::vector<glm::mat4>>();
    GenerateInstanceData();
    RecalculateBlockHeights();
}

void Chunk::GenerateInstanceData() {
    // clear if re-generating
    InstancesData_->clear();
    InstancesData_->reserve(Objects_.size());

    for (const auto& o : Objects_) {
        auto model = glm::mat4(1.0f); // identity matrix
        model = glm::translate(model, o.Position());
        model = glm::scale(model, o.Scale());

        assert(o.HasComponent<Components::SpritesheetTex>());
        const auto& texPos = o.GetComponent<Components::SpritesheetTex>().GetTexPos();
        Helpers::Math::PackVecToMatrix(model, texPos);

        InstancesData_->push_back(model);
    }
}

void Chunk::FinisChunk() {
    Objects_.shrink_to_fit();
    GenerateInstanceData();
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
