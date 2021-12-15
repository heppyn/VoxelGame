#pragma once

#include "../engine/InputHandler.h"


namespace Input {
class InputHandlerGl : public InputHandler {
  public:
    // process state of input as it is
    void ProcessInput(float delta) const override;
    // process key when action was executed on it
    // process the action just once
    void ProcessKey(int key, int scanCode, int action, int mods);
    void ProcessMouse(float xPos, float yPos) const;
    void ProcessMouseScroll(float yOffset) const;
    void Init(Renderer::Camera* actor) override;

  private:
    void SetCallBacks();
};

namespace Detail {
    static InputHandlerGl* currentHandler;
}
} // namespace Input
