#pragma once
#include <vector>

#include "GameObject.h"
#include "renderer/Camera.h"

class Scene {
  private:
    std::vector<GameObject> Lights_{};
    std::vector<GameObject> Objects_{};
    std::shared_ptr<Renderer::Camera> Camera_{ nullptr };
    int RenderDistance_{ 4 };

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

    [[nodiscard]] std::vector<GameObject>& GetObjects() {
        return Objects_;
    }

    [[nodiscard]] const std::vector<GameObject>& GetObjects() const {
        return Objects_;
    }
};
