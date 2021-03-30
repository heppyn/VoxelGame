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
        Count
    };
}

class InputHandler {
  protected:
    std::array<std::unique_ptr<Commands::Command>, Keys::Count> Commands;

public:
    InputHandler();
    virtual ~InputHandler() = default;

    void Init(Renderer::Camera* actor);
    virtual void ProcessInput(float delta) const = 0;
};
} // namespace Input
