#pragma once
#include <memory>

#include "GameObject.h"
#include "renderer/Camera.h"
#include "renderer/SceneRenderer.h"
#include "open_gl/InputHandlerGl.h"
#include "Scene.h"

class Game {
  public:
    Game() = default;
    ~Game();
    void Init();
    void ProcessInput(float delta) const;
    void Update(float delta);
    void Render() const;

    [[nodiscard]] unsigned int Width() const;
    [[nodiscard]] unsigned int Height() const;
    [[nodiscard]] Renderer::Camera* GetCamera() const { return Camera.get(); }

  private:
    std::shared_ptr<Renderer::Camera> Camera{ nullptr };
    std::unique_ptr<Renderer::SceneRenderer> Renderer{ nullptr };
    Scene Scene_;

    std::unique_ptr<Input::InputHandler> InputHandler{ new Input::InputHandlerGl };

    void InitScene();
};
