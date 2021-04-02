#include "Game.h"

#include "ResourceManager.h"
#include "../open_gl/WindowManagerGl.h"
#include "../game/TerrainGen.h"


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
    Renderer->Render(Scene, Width(), Height());
}

unsigned Game::Width() const {
    return WindowManagerGl::Width;
}

unsigned Game::Height() const {
    return WindowManagerGl::Height;
}

void Game::InitScene() {
    const auto size = Terrain::TerrainGen::GetChunkSize();

    for (unsigned int i = 0; i < 16; ++i) {
        for (unsigned int j = 0; j < 16; ++j) {
            auto tmp = Terrain::TerrainGen::GenerateChunk(glm::vec2(i * size, j * size));
            Scene.insert(Scene.end(), tmp.begin(), tmp.end());
        }
    }
}
