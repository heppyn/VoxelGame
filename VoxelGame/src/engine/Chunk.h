#pragma once

#include <vector>

#include "GameObject.h"

class Chunk {
  public:
    static float ChunkSize;
    // lowest x and z coords
    const glm::vec2 Position;

  private:
    std::vector<GameObject> Objects_;
    std::shared_ptr<std::vector<glm::mat4>> InstancesData_;

  public:
    Chunk();
    Chunk(const glm::vec2& position, std::vector<GameObject>&& objects);

    void GenerateInstanceData();
    [[nodiscard]] std::shared_ptr<std::vector<glm::mat4>> GetInstancesData() const;
    [[nodiscard]] const std::vector<GameObject>& GetObjects() const;
};
