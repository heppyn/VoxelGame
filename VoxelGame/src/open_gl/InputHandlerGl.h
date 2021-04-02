#pragma once

#include "../engine/InputHandler.h"


namespace Input {
class InputHandlerGl : public InputHandler {
  public:
    void ProcessInput(float delta) const override;
    void ProcessMouse(float xPos, float yPos) const;
    void ProcessMouseScroll(float yOffset) const;
    void Init(Renderer::Camera* actor) override;

  private:
    void SetCallBacks();
};

namespace Details {
    static InputHandlerGl* currentHandler;
}
} // namespace Input
