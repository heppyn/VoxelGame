#include "Game.h"

#include "ResourceManager.h"
#include "../open_gl/WindowManagerGl.h"
#include "../game/TerrainGen.h"


Game::~Game() {
    ResourceManager::Clear();
}

void Game::Init() {
    auto* textureShader = ResourceManager::LoadShader("./res/shaders/Texture.vs", "./res/shaders/Texture.fs", nullptr, "textureShader");
    auto* textureBatchShader = ResourceManager::LoadShader("./res/shaders/BatchTexture.vert", "./res/shaders/BatchTexture.frag", nullptr, "tBatchShader");
    auto* lightShader = ResourceManager::LoadShader("./res/shaders/Light.vert", "./res/shaders/Light.frag", nullptr, "light");
    ResourceManager::LoadShader("./res/shaders/Mesh.vert", "./res/shaders/Mesh.frag", nullptr, "meshShader");
    // texture is loaded from texture unit 0
    textureShader->SetInteger("texture1", 0, true);
    textureBatchShader->SetInteger("texture1", 0, true);
    lightShader->SetInteger("texture1", 0, true);

    ResourceManager::LoadTexture2D("./res/textures/box.png", true, "boxTexture");
    ResourceManager::LoadTexture2D("./res/textures/white.png", true, "white");

    Camera = std::make_unique<Renderer::Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    Renderer = std::make_unique<Renderer::SceneRenderer>(Camera.get());

    InitScene();
    InputHandler->Init(Camera.get());
}

void Game::ProcessInput(float delta) const {
    InputHandler->ProcessInput(delta);
}

void Game::Update(float delta) {
}

void Game::Render() const {
    Renderer->Render(Scene_, Width(), Height());
}

unsigned Game::Width() const {
    return WindowManagerGl::Width;
}

unsigned Game::Height() const {
    return WindowManagerGl::Height;
}

void Game::InitScene() {
    Scene_.Init();
}
