#pragma once

#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer/Camera.h"
#include "engine/Game.h"
#include "open_gl/WindowManagerGl.h"
#include "engine/Log.h"


extern Game* Engine::CreateGame();

#ifdef VXL_PROVIDED_TEST_RUNNER
extern std::function<int()> Engine::GetTestRunner();
#else
namespace Engine {
std::function<int()> GetTestRunner() {
    return []() { return 0; };
}
} // namespace Engine
#endif

Game* game = Engine::CreateGame();
Renderer::Camera* camera;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

int main(const int argc, const char* argv[]) {
    auto* window = WindowManagerGl::CreateMainWindow(true);
    if (!window) {
        LOG_ENGINE_CRITICAL("Window was not created");
        return 1;
    }
    glfwSetFramebufferSizeCallback(window, WindowManagerGl::FramebufferSizeCallback);

    game->Init();
    camera = game->GetCamera();

    if (const int result = Engine::GetTestRunner()(); result) {
        return result;
    }

    // only terrain generator is supposed to run
    if (argc >= 2 && (std::string(argv[1]) == "--export" || std::string(argv[1]) == "-e")) {
        game->ExportScene();
    }
    else {
        WindowManagerGl::ShowWindow();
        while (game->IsRunning()) {
            const auto currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            // LOG_ENGINE_INFO("FPS: {}", 1.0f / deltaTime);

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
