#pragma once
#include <memory>
#include <array>

#include "Commands.h"


namespace Input {
namespace Keys {
    /**
     * \brief All available keys which can have bindings
     */
    enum Keys {
        W,
        S,
        A,
        D,
        P,
        Count
    };
} // namespace Keys

/**
 * \brief Abstract class for processing input
 * key actions can be changed by providing new Command
 */
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
