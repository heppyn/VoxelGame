#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "renderer/Camera.h"
#include "engine/Game.h"
#include "open_gl/WindowManagerGl.h"

#define CATCH_CONFIG_RUNNER
#include "../tests/vendor/catch.hpp"


// camera
Game* game = new Game;
Renderer::Camera* camera;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

int main(const int argc, const char* argv[]) {
    auto* window = WindowManagerGl::CreateMainWindow(true);
    if (!window) {
        std::cout << "Window was not created\n";
        return 1;
    }
    glfwSetFramebufferSizeCallback(window, WindowManagerGl::FramebufferSizeCallback);

    game->Init();
    camera = game->GetCamera();

    // first initialize game to use resource manager etc.
    // add -s to see successful runs
    //const char* params[] = { "main", "-s" };

#ifdef TEST_ONLY
    constexpr auto testOnly = true;
#else
    constexpr auto testOnly = false;
#endif

    if (const int result = Catch::Session().run(); result || testOnly) {
        std::cin.ignore();
        return result;
    }

    // only terrain generator is supposed to run
    if (argc >= 2 && (std::string(argv[1]) == "--export" || std::string(argv[1]) == "-e")) {
        game->ExportScene();
    }
    else {
        WindowManagerGl::ShowWindow();
        while (!game->Finished()) {
            const auto currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            //std::cout << "FPS: " << 1.0f / deltaTime << '\n';

            game->ProcessInput(deltaTime);
            game->Update(deltaTime);
            game->Render();
        }
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    delete game;
    glfwTerminate();
    return 0;
}
