#include "WindowManagerGl.h"

#include <iostream>

#include "renderer/Debug.h"


GLFWwindow* WindowManagerGl::MainWindow = nullptr;
unsigned int WindowManagerGl::Width = 1500;
unsigned int WindowManagerGl::Height = 800;

void ErrorCallback(int, const char* error) {
    std::cout << "GLFW Error: " << error << std::endl;
}

GLFWwindow* WindowManagerGl::CreateMainWindow(bool debug /*= false*/) {
    // glfw: initialize and configure
    glfwSetErrorCallback(ErrorCallback);
    glfwInit();
    // debug is supported from 4.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, debug);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    MainWindow = glfwCreateWindow(Width, Height, "Voxel Game", nullptr, nullptr);
    if (MainWindow == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(MainWindow);

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

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);

    return MainWindow;
}

void WindowManagerGl::CloseMainWindow() {
    glfwSetWindowShouldClose(MainWindow, true);
}

bool WindowManagerGl::ShouldCloseMainWindow() {
    return glfwWindowShouldClose(MainWindow);
}

void WindowManagerGl::MaximizeWindow() {
    glfwMaximizeWindow(MainWindow);
}

void WindowManagerGl::ShowWindow() {
    glfwSetInputMode(MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwShowWindow(MainWindow);
}

void WindowManagerGl::SetCursorPosCallback(GLFWcursorposfun callback) {
    glfwSetCursorPosCallback(MainWindow, callback);
}

void WindowManagerGl::SetScrollCallback(GLFWcursorposfun callback) {
    glfwSetScrollCallback(MainWindow, callback);
}

void WindowManagerGl::SetKeyCallback(GLFWkeyfun callback) {
    glfwSetKeyCallback(MainWindow, callback);
}

void WindowManagerGl::FramebufferSizeCallback([[maybe_unused]] GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions
    // TODO: implement observer to update
    // TODO: more windows?
    Width = static_cast<unsigned int>(width);
    Height = static_cast<unsigned int>(height);
    glViewport(0, 0, width, height);
}

void WindowManagerGl::EndFrame() {
    glfwSwapBuffers(MainWindow);
    glfwPollEvents();
}
