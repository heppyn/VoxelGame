#pragma once
#include <memory>

#include "renderer/Camera.h"
#include "renderer/SceneRenderer.h"

class Game {
  public:
    bool Keys[1024];
    unsigned int Width, Height;

    Game(unsigned int width, unsigned int height);
    ~Game();
    void Init();
    void ProcessInput(float delta);
    void Update(float delta);
    void Render() const;

    [[nodiscard]] Renderer::Camera* GetCamera() const { return Camera.get(); }

  private:
    std::unique_ptr<Renderer::Camera> Camera{ nullptr };
    std::unique_ptr<Renderer::SceneRenderer> Renderer{ nullptr };
    std::vector<glm::vec3> Scene{};
};