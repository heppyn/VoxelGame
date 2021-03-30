#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class WindowManagerGl {
  public:
    static GLFWwindow* MainWindow;
    static unsigned int Width;
    static unsigned int Height;

    static GLFWwindow* CreateMainWindow();
    static void CloseMainWindow();

private:
    // singleton
    WindowManagerGl() = default;
};
