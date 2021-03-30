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
    /**
     * \brief glfw: whenever the window size changed (by OS or user resize) this callback function executes
     * \param window window which size is changed
     * \param width new width
     * \param height new height
     */
    static void FramebufferSizeCallback([[maybe_unused]] GLFWwindow* window, int width, int height);

  private:
    // singleton
    WindowManagerGl() = default;
};
