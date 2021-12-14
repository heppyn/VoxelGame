#include "InputHandlerGl.h"

#include "WindowManagerGl.h"


namespace Input::Detail {
void CursorPosCallback(GLFWwindow*, double xPos, double yPos) {
    Details::currentHandler->ProcessMouse(static_cast<float>(xPos), static_cast<float>(yPos));
}

void ScrollCallback(GLFWwindow*, double, double yOffset) {
    Details::currentHandler->ProcessMouseScroll(static_cast<float>(yOffset));
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
    Details::currentHandler = this;
    WindowManagerGl::SetCursorPosCallback(Detail::CursorPosCallback);
    WindowManagerGl::SetScrollCallback(Detail::ScrollCallback);
}
