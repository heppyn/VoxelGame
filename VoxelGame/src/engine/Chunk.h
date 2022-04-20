#pragma once

#include <vector>

#include "GameObject.h"
#include "BlockInfo.h"
#include "BlockFaces.h"

class Chunk {
  public:
    static float ChunkSize;
    // lowest x and z coords
    const glm::vec2 Position;

    // default cube has six sides
    inline static Engine::Cube::BlockFaces DefaultCube_{ Engine::Cube::BlockFaces::CreateBlockFaces(Engine::Cube::Faces::ALL) };

  private:
    std::map<Engine::Cube::BlockFaces, std::vector<GameObject>> Objects_;
    std::map<Engine::Cube::BlockFaces, std::vector<GameObject>> ObjectsTrans_;

    std::map<Engine::Cube::BlockFaces, std::shared_ptr<std::vector<glm::mat4>>> InstancesData_;
    // separate transparent textures from non transparent, so semi transparent textures are correctly blended
    std::map<Engine::Cube::BlockFaces, std::shared_ptr<std::vector<glm::mat4>>> InstancesDataTrans_;
    // vector of rows in chunk
    // [0, 1], [1, 1]
    // [0, 0], [1, 0]
    std::vector<std::vector<BlockInfo>> BlockInfos_;
    glm::vec3 PositionInSpace_;

  public:
    explicit Chunk(const glm::vec2& position);
    Chunk(const glm::vec2& position, std::vector<GameObject>&& objects);

    void GenerateInstanceData();
    /**
     * Call after all objects are added.
     * Shrinks objects buffers and generates objects data.
     */
    void FinisChunk();

    void AddObjectData(std::vector<glm::mat4>&& objects);
    void AddObject(GameObject&& object, Engine::Cube::BlockFaces faces = DefaultCube_);
    void AddObjects(std::vector<GameObject>&& objects, Engine::Cube::BlockFaces faces = DefaultCube_);
    void AddObjectTrans(GameObject&& object, Engine::Cube::BlockFaces faces = DefaultCube_);
    void AddObjectsTrans(std::vector<GameObject>&& objects, Engine::Cube::BlockFaces faces = DefaultCube_);

    [[nodiscard]] const std::map<Engine::Cube::BlockFaces, std::shared_ptr<std::vector<glm::mat4>>>& GetInstancesData() const;
    [[nodiscard]] std::map<Engine::Cube::BlockFaces, std::shared_ptr<std::vector<glm::mat4>>>& GetInstancesData();
    [[nodiscard]] const std::map<Engine::Cube::BlockFaces, std::vector<GameObject>>& GetObjects() const;
    [[nodiscard]] std::map<Engine::Cube::BlockFaces, std::vector<GameObject>>& GetObjects();

    [[nodiscard]] const std::map<Engine::Cube::BlockFaces, std::shared_ptr<std::vector<glm::mat4>>>& GetInstancesDataTrans() const;
    [[nodiscard]] std::map<Engine::Cube::BlockFaces, std::shared_ptr<std::vector<glm::mat4>>>& GetInstancesDataTrans();
    [[nodiscard]] const std::map<Engine::Cube::BlockFaces, std::vector<GameObject>>& GetObjectsTrans() const;
    [[nodiscard]] std::map<Engine::Cube::BlockFaces, std::vector<GameObject>>& GetObjectsTrans();

    [[nodiscard]] BlockInfo& GetBlockInfo(const glm::vec2& pos);
    [[nodiscard]] BlockInfo& GetBlockInfo(const glm::vec3& pos);
    [[nodiscard]] const std::vector<std::vector<BlockInfo>>& GetBlockInfos() const { return BlockInfos_; }


    /**
     * \brief Lowest position in chunk.
     * \return chunk start position with lowest y position in chunk
     */
    [[nodiscard]] glm::vec3 PositionInSpace() const { return PositionInSpace_; }
    [[nodiscard]] size_t GenNumberOfObjects() const;

  private:
    void RecalculateBlockHeights();
    static void GenerateInstanceData(
      const std::map<Engine::Cube::BlockFaces, std::vector<GameObject>>& objects,
      std::map<Engine::Cube::BlockFaces, std::shared_ptr<std::vector<glm::mat4>>>& buffer);
    void SetPositionInSpace();
};
