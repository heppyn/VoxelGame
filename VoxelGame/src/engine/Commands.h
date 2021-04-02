#pragma once
#include "../renderer/Camera.h"

namespace Commands {
class Command {
  protected:
    // TODO: change to game object
    Renderer::Camera* Actor;

  public:
    explicit Command(Renderer::Camera* actor) : Actor(actor) {}
    virtual ~Command() = default;

    virtual void Execute(float delta) = 0;
};

class NullCommand : public Command {
  public:
    NullCommand() : NullCommand(nullptr) {}
    explicit NullCommand(Renderer::Camera*) : Command(nullptr) {}
    void Execute(float) override {}
};

class MoveForwardCommand : public Command {
  public:
    explicit MoveForwardCommand(Renderer::Camera* actor) : Command(actor) {}
    void Execute(float delta) override;
};
class MoveBackCommand : public Command {
  public:
    explicit MoveBackCommand(Renderer::Camera* actor) : Command(actor) {}
    void Execute(float delta) override;
};
class MoveLeftCommand : public Command {
  public:
    explicit MoveLeftCommand(Renderer::Camera* actor) : Command(actor) {}
    void Execute(float delta) override;
};
class MoveRightCommand : public Command {
  public:
    explicit MoveRightCommand(Renderer::Camera* actor) : Command(actor) {}
    void Execute(float delta) override;
};

class MouseCommand {
  protected:
    // TODO: change to game object
    Renderer::Camera* Actor;
    bool FirstMouse{ true };
    float LastX{ 0 };
    float LastY{ 0 };

  public:
    explicit MouseCommand(Renderer::Camera* actor) : Actor(actor) {}
    virtual ~MouseCommand() = default;

    virtual void ExecuteMove(float xPos, float yPos);
    virtual void ExecuteScroll(float yOffset);
};

class MouseCommandNull : public MouseCommand
{
public:
    MouseCommandNull() : MouseCommandNull(nullptr) {}
    explicit MouseCommandNull(Renderer::Camera* actor) : MouseCommand(actor) {}

    void ExecuteMove(float, float) override {}
    void ExecuteScroll(float) override {}
};
} // namespace Commands
