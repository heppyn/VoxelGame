#pragma once
#include <vector>
#include <map>

#include "Chunk.h"
#include "GameObject.h"
#include "renderer/Camera.h"
#include "helpers/Math.h"

struct GlobalLight {
    glm::vec3 Direction;
    glm::vec3 Color;
};

class Scene {
  private:
    // default is light off
    GlobalLight GlobalLight_{ glm::vec3(0), glm::vec3(0) };
    std::vector<GameObject> Lights_{};
    std::map<glm::vec2, Chunk, Helpers::CmpGlmVec<glm::vec2>> Chunks_{};
    std::shared_ptr<Renderer::Camera> Camera_{ nullptr };
    int RenderDistance_{ 8 };

    std::map<Engine::Cube::BlockFaces, std::vector<std::shared_ptr<std::vector<glm::mat4>>>> ObjectsDataCache_{};

  public:
    void Init(std::shared_ptr<Renderer::Camera> camera);
    void Update(bool updateAll = false);
    // original game scene update, disabled for testing purposes
    void UpdateOrig(bool updateAll = false);
    void SetCamera(std::shared_ptr<Renderer::Camera> camera);

    [[nodiscard]] std::vector<GameObject>& GetLights() {
        return Lights_;
    }
    [[nodiscard]] const std::vector<GameObject>& GetLights() const {
        return Lights_;
    }
    [[nodiscard]] const GlobalLight& GetGlobalLight() const {
        return GlobalLight_;
    }
    void SetGlobalLight(const GlobalLight& light) {
        GlobalLight_ = light;
    }

    void SetRenderDistance(int distance) { RenderDistance_ = distance; }

    [[nodiscard]] const std::map<glm::vec2, Chunk, Helpers::CmpGlmVec<glm::vec2>>& GetChunks() const;
    [[nodiscard]] const std::map<Engine::Cube::BlockFaces, std::vector<std::shared_ptr<std::vector<glm::mat4>>>>& GetRenderableObjectsData() const;
    [[nodiscard]] size_t GetSceneSize(const Engine::Cube::BlockFaces& faces) const;
    [[nodiscard]] bool IsInRenderDistance(const Chunk& chunk) const;
    [[nodiscard]] static bool IsChunkInView(const glm::vec3& position, const glm::vec3& observer, const glm::mat4& projView);
    [[nodiscard]] static bool IsPointInView(const glm::vec3& position, const glm::mat4& projView);

  private:
    [[nodiscard]] glm::vec2 GetCenterChunkPos() const;
    void UpdateObjectsData();
    [[nodiscard]] glm::mat4 ProjViewMatrix() const;
};
