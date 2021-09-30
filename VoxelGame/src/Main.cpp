#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "renderer/Camera.h"
#include "renderer/Shader.h"
#include "engine/Game.h"
#include "open_gl/WindowManagerGl.h"

#include "../tests/TestRunner.h"


// camera
Game* game = new Game;
Renderer::Camera* camera;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

int main() {
    Tests::TestRunner::RunTests();

    // enable debug by passing true
    auto* window = WindowManagerGl::CreateMainWindow(true);
    glfwSetFramebufferSizeCallback(window, WindowManagerGl::FramebufferSizeCallback);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    game->Init();
    camera = game->GetCamera();

    while (!glfwWindowShouldClose(window)) {
        const float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //std::cout << "FPS: " << 1.0f / deltaTime << '\n';

        game->ProcessInput(deltaTime);
        game->Update(deltaTime);
        game->Render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    delete game;
    glfwTerminate();
    return 0;
}
