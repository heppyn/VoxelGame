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
