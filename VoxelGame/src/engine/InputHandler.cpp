#include "InputHandler.h"

Input::InputHandler::InputHandler() {
    for (auto& command : Commands) {
        command = std::make_unique<Commands::NullCommand>();
    }
}

void Input::InputHandler::Init(Renderer::Camera* actor) {
    Commands[Keys::W] = std::make_unique<Commands::MoveForwardCommand>(actor);
    Commands[Keys::S] = std::make_unique<Commands::MoveBackCommand>(actor);
    Commands[Keys::A] = std::make_unique<Commands::MoveLeftCommand>(actor);
    Commands[Keys::D] = std::make_unique<Commands::MoveRightCommand>(actor);
}
