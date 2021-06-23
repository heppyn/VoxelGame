#include "Chunk.h"

#include "Components/Mesh.h"
#include "helpers/Math.h"

float Chunk::ChunkSize{ 16 };

Chunk::Chunk()
  : Position(0) {
}

Chunk::Chunk(const glm::vec2& position, std::vector<GameObject>&& objects)
  : Position(position), Objects_(std::move(objects)) {
    InstancesData_ = std::make_shared<std::vector<glm::mat4>>();
    GenerateInstanceData();
}

void Chunk::GenerateInstanceData() {
    // clear if re-generating
    InstancesData_->clear();
    InstancesData_->reserve(Objects_.size());

    for (const auto& o : Objects_) {
        auto model = glm::mat4(1.0f); // identity matrix
        model = glm::translate(model, o.Position());
        model = glm::scale(model, o.Scale());

        assert(o.HasComponent<Components::Mesh>());
        const auto& texPos = o.GetComponent<Components::Mesh>().Mesh_.GetTexPos();
        Helpers::Math::PackVecToMatrix(model, texPos);

        InstancesData_->push_back(model);
    }
}

std::shared_ptr<std::vector<glm::mat4>> Chunk::GetInstancesData() const {
    assert(!InstancesData_->empty());

    return InstancesData_;
}

const std::vector<GameObject>& Chunk::GetObjects() const
{
    return Objects_;
}
