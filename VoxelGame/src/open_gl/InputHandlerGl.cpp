#include "InputHandlerGl.h"

#include "WindowManagerGl.h"


namespace Input::Detail {
void CursorPosCallback(GLFWwindow*, double xPos, double yPos) {
    currentHandler->ProcessMouse(static_cast<float>(xPos), static_cast<float>(yPos));
}

void ScrollCallback(GLFWwindow*, double, double yOffset) {
    currentHandler->ProcessMouseScroll(static_cast<float>(yOffset));
}

void KeyCallback(GLFWwindow*, int key, int scanCode, int action, int mods) {
    currentHandler->ProcessKey(key, scanCode, action, mods);
}
} // namespace Input::Detail

void Input::InputHandlerGl::ProcessInput(float delta) const {
    auto* window = WindowManagerGl::MainWindow;

    // TODO: consider doing this as a command
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        WindowManagerGl::CloseMainWindow();
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        WindowManagerGl::MaximizeWindow();
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

void Input::InputHandlerGl::ProcessKey(int key, [[maybe_unused]] int scanCode, int action, [[maybe_unused]] int mods) {
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        // delta is not relevant for stopping camera
        Commands[Keys::P]->Execute(0.0f);
    }
}

void Input::InputHandlerGl::ProcessMouse(float xPos, float yPos) const {
    MouseCommand->ExecuteMove(xPos, yPos);
}

void Input::InputHandlerGl::ProcessMouseScroll(float yOffset) const {
    MouseCommand->ExecuteScroll(yOffset);
}

void Input::InputHandlerGl::Init(Renderer::Camera* actor) {
    InputHandler::Init(actor);
    SetCallBacks();
}

void Input::InputHandlerGl::SetCallBacks() {
    Detail::currentHandler = this;
    WindowManagerGl::SetCursorPosCallback(Detail::CursorPosCallback);
    WindowManagerGl::SetScrollCallback(Detail::ScrollCallback);
    WindowManagerGl::SetKeyCallback(Detail::KeyCallback);
}
