#include "Game.h"

#include "renderer/ResourceManager.h"

Game::Game(unsigned width, unsigned height)
  : Width(width), Height(height) {
    Scene = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };
}

Game::~Game() {
    ResourceManager::Clear();
}

void Game::Init() {
    Camera = std::make_unique<Renderer::Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    Renderer = std::make_unique<Renderer::SceneRenderer>(Camera.get());
}

void Game::ProcessInput(float delta) {
}

void Game::Update(float delta) {
}

void Game::Render() const {
    Renderer->Render(Scene, Width, Height);
}
