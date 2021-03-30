#include "Game.h"

#include "ResourceManager.h"

Game::Game(unsigned width, unsigned height)
  : Width(width), Height(height) {
}

Game::~Game() {
    ResourceManager::Clear();
}

void Game::Init() {
    auto* textureShader = ResourceManager::LoadShader("./res/shaders/Texture.vs", "./res/shaders/Texture.fs", nullptr, "textureShader");
    // texture is loaded from texture unit 0
    textureShader->SetInteger("texture1", 0);

    ResourceManager::LoadTexture2D("./res/textures/box.png", true, "boxTexture");

    Camera = std::make_unique<Renderer::Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    Renderer = std::make_unique<Renderer::SceneRenderer>(Camera.get());

    InitScene();
    InputHandler->Init(Camera.get());
}

void Game::ProcessInput(float delta) {
    InputHandler->ProcessInput(delta);
}

void Game::Update(float delta) {
}

void Game::Render() const {
    Renderer->Render(Scene, Width, Height);
}

void Game::InitScene() {
    Scene = {
        GameObject(glm::vec3(2.0f, 5.0f, -15.0f), ResourceManager::GetTexture2D("boxTexture")),
        GameObject(glm::vec3(-1.5f, -2.2f, -2.5f), ResourceManager::GetTexture2D("boxTexture")),
        GameObject(glm::vec3(-3.8f, -2.0f, -12.3f), ResourceManager::GetTexture2D("boxTexture")),
        GameObject(glm::vec3(2.4f, -0.4f, -3.5f), ResourceManager::GetTexture2D("boxTexture")),
        GameObject(glm::vec3(-1.7f, 3.0f, -7.5f), ResourceManager::GetTexture2D("boxTexture")),
        GameObject(glm::vec3(1.3f, -2.0f, -2.5f), ResourceManager::GetTexture2D("boxTexture")),
        GameObject(glm::vec3(1.5f, 2.0f, -2.5f), ResourceManager::GetTexture2D("boxTexture")),
        GameObject(glm::vec3(0.0f, 0.0f, 0.0f), ResourceManager::GetTexture2D("boxTexture")),
        GameObject(glm::vec3(1.5f, 0.2f, -1.5f), ResourceManager::GetTexture2D("boxTexture")),
        GameObject(glm::vec3(-1.3f, 1.0f, -1.5f), ResourceManager::GetTexture2D("boxTexture")),
    };
}
