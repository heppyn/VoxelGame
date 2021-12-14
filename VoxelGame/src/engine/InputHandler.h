#pragma once
#include <memory>
#include <array>

#include "Commands.h"


namespace Input {
namespace Keys {
    enum Keys {
        W,
        S,
        A,
        D,
        P,
        Count
    };
}

class InputHandler {
  protected:
    std::array<std::unique_ptr<Commands::Command>, Keys::Count> Commands;
    std::unique_ptr<Commands::MouseCommand> MouseCommand;

public:
    InputHandler();
    virtual ~InputHandler() = default;

    virtual void Init(Renderer::Camera* actor);
    virtual void ProcessInput(float delta) const = 0;
};
} // namespace Input
