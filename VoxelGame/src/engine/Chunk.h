#pragma once

#include <vector>

#include "GameObject.h"
#include "BlockInfo.h"

class Chunk {
  public:
    static float ChunkSize;
    // lowest x and z coords
    const glm::vec2 Position;

  private:
    std::vector<GameObject> Objects_;
    std::shared_ptr<std::vector<glm::mat4>> InstancesData_;
    std::vector<std::vector<BlockInfo>> BlockInfos_;

  public:
    explicit Chunk(const glm::vec2& position);
    Chunk(const glm::vec2& position, std::vector<GameObject>&& objects);

    void GenerateInstanceData();
    void FinisChunk();
    [[nodiscard]] std::shared_ptr<std::vector<glm::mat4>> GetInstancesData() const;
    [[nodiscard]] const std::vector<GameObject>& GetObjects() const;
    [[nodiscard]] std::vector<GameObject>& GetObjects();

  private:
    void RecalculateBlockHeights();
};
