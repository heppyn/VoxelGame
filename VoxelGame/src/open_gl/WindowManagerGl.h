#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class WindowManagerGl {
  public:
    static GLFWwindow* MainWindow;
    static unsigned int Width;
    static unsigned int Height;

    static GLFWwindow* CreateMainWindow(bool debug = false);
    static void CloseMainWindow();
    static bool ShouldCloseMainWindow();
    static void MaximizeWindow();
    static void ShowWindow();
    static void SetCursorPosCallback(GLFWcursorposfun callback);
    static void SetScrollCallback(GLFWcursorposfun callback);
    static void SetKeyCallback(GLFWkeyfun callback);
    /**
     * \brief glfw: whenever the window size changed (by OS or user resize) this callback function executes
     * \param window window which size is changed
     * \param width new width
     * \param height new height
     */
    static void FramebufferSizeCallback([[maybe_unused]] GLFWwindow* window, int width, int height);
    /**
     * \brief swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
     */
    static void EndFrame();

  private:
    // singleton
    WindowManagerGl() = default;
};
