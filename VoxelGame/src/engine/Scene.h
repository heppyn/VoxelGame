#pragma once
#include <vector>
#include <map>


#include "Chunk.h"
#include "GameObject.h"
#include "renderer/Camera.h"
#include "helpers/Math.h"

class Scene {
  private:
    std::vector<GameObject> Lights_{};
    std::map<glm::vec2, Chunk, Helpers::CmpGlmVec<glm::vec2>> Chunks_{};
    std::shared_ptr<Renderer::Camera> Camera_{ nullptr };
    int RenderDistance_{ 2 };

  public:
    void Init(std::shared_ptr<Renderer::Camera> camera);
    void Update();
    void SetCamera(std::shared_ptr<Renderer::Camera> camera);

    [[nodiscard]] std::vector<GameObject>& GetLights() {
        return Lights_;
    }

    [[nodiscard]] const std::vector<GameObject>& GetLights() const {
        return Lights_;
    }

    [[nodiscard]] const std::map<glm::vec2, Chunk, Helpers::CmpGlmVec<glm::vec2>>& GetChunks() const;
    [[nodiscard]] std::vector<std::shared_ptr<std::vector<glm::mat4>>> GetRenderableObjectsData() const;
    [[nodiscard]] size_t GetSceneSize() const;

private:
    [[nodiscard]] glm::vec2 GetCenterChunkPos() const;
};
