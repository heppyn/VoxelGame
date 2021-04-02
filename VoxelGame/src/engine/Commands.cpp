#include "Commands.h"

void Commands::MoveForwardCommand::Execute(float delta)
{
    Actor->Move(delta, 0.0, 1.0);
}

void Commands::MoveBackCommand::Execute(float delta)
{
    Actor->Move(delta, 0.0, -1.0);
}

void Commands::MoveLeftCommand::Execute(float delta)
{
    Actor->Move(delta, -1.0);
}

void Commands::MoveRightCommand::Execute(float delta)
{
    Actor->Move(delta, 1.0);
}

void Commands::MouseCommand::ExecuteMove(float xPos, float yPos) {
    if (FirstMouse) {
        LastX = static_cast<float>(xPos);
        LastY = static_cast<float>(yPos);
        FirstMouse = false;
    }

    const float xOffset = static_cast<float>(xPos) - LastX;
    const float yOffset = LastY - static_cast<float>(yPos); // reversed since y-coordinates go from bottom to top

    LastX = static_cast<float>(xPos);
    LastY = static_cast<float>(yPos);
    Actor->ProcessMouseMovement(xOffset, yOffset);
}

void Commands::MouseCommand::ExecuteScroll(float yOffset)
{
    Actor->ProcessMouseScroll(yOffset);
}
