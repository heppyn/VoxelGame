#include "WindowManagerGl.h"

#include <iostream>

#include "renderer/Debug.h"

//#include "../renderer/Debug.h"


GLFWwindow* WindowManagerGl::MainWindow = nullptr;
unsigned int WindowManagerGl::Width = 1500;
unsigned int WindowManagerGl::Height = 800;

GLFWwindow* WindowManagerGl::CreateMainWindow(bool debug /*= false*/) {
    // glfw: initialize and configure
    glfwInit();
    // debug is supported from 4.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, debug);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    MainWindow = glfwCreateWindow(Width, Height, "Voxel Game", nullptr, nullptr);
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

    if (debug) {
        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            // initialize debug output
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(GlDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
            std::cout << "Debug initialized\n";
        }
    }

    return MainWindow;
}

void WindowManagerGl::CloseMainWindow() {
    glfwSetWindowShouldClose(MainWindow, true);
}

void WindowManagerGl::MaximizeWindow() {
    glfwMaximizeWindow(MainWindow);
}

void WindowManagerGl::SetCursorPosCallback(GLFWcursorposfun callback) {
    glfwSetCursorPosCallback(MainWindow, callback);
}

void WindowManagerGl::SetScrollCallback(GLFWcursorposfun callback) {
    glfwSetScrollCallback(MainWindow, callback);
}

void WindowManagerGl::FramebufferSizeCallback([[maybe_unused]] GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions
    // TODO: implement observer to update
    // TODO: more windows?
    Width = static_cast<unsigned int>(width);
    Height = static_cast<unsigned int>(height);
    glViewport(0, 0, width, height);
}
