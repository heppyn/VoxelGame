#pragma once
#include <memory>

#include "GameObject.h"
#include "renderer/Camera.h"
#include "renderer/SceneRenderer.h"
#include "open_gl/InputHandlerGl.h"

class Game {
  public:
    Game() = default;
    ~Game();
    void Init();
    void ProcessInput(float delta);
    void Update(float delta);
    void Render() const;

    [[nodiscard]] unsigned int Width() const;
    [[nodiscard]] unsigned int Height() const;
    [[nodiscard]] Renderer::Camera* GetCamera() const { return Camera.get(); }

  private:
    std::unique_ptr<Renderer::Camera> Camera{ nullptr };
    std::unique_ptr<Renderer::SceneRenderer> Renderer{ nullptr };
    std::vector<GameObject> Scene{};

    std::unique_ptr<Input::InputHandler> InputHandler{ new Input::InputHandlerGl };

    void InitScene();
};
