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
    std::vector<GameObject> ObjectsTrans_;
    std::shared_ptr<std::vector<glm::mat4>> InstancesData_;
    // separate transparent textures from non transparent, so semi transparent textures are correctly blended
    std::shared_ptr<std::vector<glm::mat4>> InstancesDataTrans_;
    // vector of rows in chunk
    // [0, 1], [1, 1]
    // [0, 0], [1, 0]
    std::vector<std::vector<BlockInfo>> BlockInfos_;

  public:
    explicit Chunk(const glm::vec2& position);
    Chunk(const glm::vec2& position, std::vector<GameObject>&& objects);

    void GenerateInstanceData();
    void FinisChunk();
    void AddObjectData(std::vector<glm::mat4>&& objects);

    [[nodiscard]] std::shared_ptr<std::vector<glm::mat4>> GetInstancesData() const;
    [[nodiscard]] const std::vector<GameObject>& GetObjects() const;
    [[nodiscard]] std::vector<GameObject>& GetObjects();

    [[nodiscard]] std::shared_ptr<std::vector<glm::mat4>> GetInstancesDataTrans() const;
    [[nodiscard]] const std::vector<GameObject>& GetObjectsTrans() const;
    [[nodiscard]] std::vector<GameObject>& GetObjectsTrans();

    [[nodiscard]] BlockInfo& GetBlockInfo(const glm::vec2& pos);
    [[nodiscard]] BlockInfo& GetBlockInfo(const glm::vec3& pos);
    [[nodiscard]] const std::vector<std::vector<BlockInfo>>& GetBlockInfos() const { return BlockInfos_; }

  private:
    void RecalculateBlockHeights();
    static void GenerateInstanceData(const std::vector<GameObject>& objects, std::shared_ptr<std::vector<glm::mat4>> buffer);
};
