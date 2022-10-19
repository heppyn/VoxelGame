#pragma once
#include <memory>

#include "GameObject.h"
#include "renderer/Camera.h"
#include "renderer/SceneRenderer.h"
#include "open_gl/InputHandlerGl.h"
#include "Scene.h"

/**
 * \brief Main class responsible for systems initiation
 */
class Game {
  public:
    Game();
    virtual ~Game();
    virtual void Init();
    void InitScene();
    void ProcessInput(float delta) const;
    virtual void Update(float delta);
    void Render() const;
    void ExportScene();

    [[nodiscard]] bool IsRunning() const;
    [[nodiscard]] Renderer::Camera* GetCamera() const { return Camera.get(); }

  protected:
    // TODO: rename to Camera_
    std::shared_ptr<Renderer::Camera> Camera{ nullptr };
    Scene Scene_;


  private:
    std::unique_ptr<Renderer::SceneRenderer> Renderer{ nullptr };
    std::unique_ptr<Input::InputHandler> InputHandler{ new Input::InputHandlerGl };
};

namespace Engine {
// to be defined in the client
Game* CreateGame();
} // namespace Engine
