#include "InputHandlerGl.h"

#include <GLFW/glfw3.h>

#include "WindowManagerGl.h"

void Input::InputHandlerGl::ProcessInput(float delta) const {
    auto* window = WindowManagerGl::MainWindow;

    // TODO: consider doing this as a command
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        WindowManagerGl::CloseMainWindow();
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        Commands[Keys::W]->Execute(delta);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        Commands[Keys::S]->Execute(delta);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        Commands[Keys::A]->Execute(delta);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        Commands[Keys::D]->Execute(delta);
    }
}
