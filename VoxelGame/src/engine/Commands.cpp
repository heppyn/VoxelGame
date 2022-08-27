#include "Commands.h"

void Commands::MoveForwardCommand::Execute([[maybe_unused]] float delta) {
    Actor->Move(delta, 0.0, 1.0);
}

void Commands::MoveBackCommand::Execute([[maybe_unused]] float delta) {
    Actor->Move(delta, 0.0, -1.0);
}

void Commands::MoveLeftCommand::Execute([[maybe_unused]] float delta) {
    Actor->Move(delta, -1.0);
}

void Commands::MoveRightCommand::Execute([[maybe_unused]] float delta) {
    Actor->Move(delta, 1.0);
}

void Commands::SwitchPauseCommand::Execute([[maybe_unused]] float delta) {
    Actor->SwitchStopState();
}

void Commands::MouseCommand::ExecuteMove(float xPos, float yPos) {
    if (FirstMouse) {
        LastX = xPos;
        LastY = yPos;
        FirstMouse = false;
    }

    const float xOffset = xPos - LastX;
    const float yOffset = LastY - yPos; // reversed since y-coordinates go from bottom to top

    LastX = xPos;
    LastY = yPos;
    Actor->ProcessMouseMovement(xOffset, yOffset);
}

void Commands::MouseCommand::ExecuteScroll(float yOffset) {
    Actor->ProcessMouseScroll(yOffset);
}
