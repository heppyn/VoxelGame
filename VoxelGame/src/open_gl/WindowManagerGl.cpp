#include "WindowManagerGl.h"

#include <iostream>

GLFWwindow* WindowManagerGl::MainWindow = nullptr;
unsigned int WindowManagerGl::Width = 1000;
unsigned int WindowManagerGl::Height = 800;

GLFWwindow* WindowManagerGl::CreateMainWindow() {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    MainWindow = glfwCreateWindow(Width, Height, "LearnOpenGL", nullptr, nullptr);
    if (MainWindow == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(MainWindow);

    // tell GLFW to capture mouse
    glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    return MainWindow;
}
