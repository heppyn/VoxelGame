#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>

#include "stb_image/stb_image.h"
#include "../helpers/Constants.h"

std::map<std::string, std::unique_ptr<Renderer::Shader>> ResourceManager::Shaders;
std::map<std::string, std::unique_ptr<Renderer::Texture2D>> ResourceManager::Textures;
std::map<std::string, std::array<const char*, 3>> ResourceManager::ShaderSources_;
Renderer::SpriteSheet ResourceManager::SpriteSheet;

Renderer::Shader* ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name) {
    Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    ShaderSources_[name] = { vShaderFile, fShaderFile, gShaderFile };
    return Shaders[name].get();
}

Renderer::Shader* ResourceManager::SetShaderMacros(const std::string& name, const ShaderMacros_t& macros) {
    assert(Shaders.contains(name));
    assert(ShaderSources_.contains(name));

    Shaders[name] = LoadShaderFromFile(
      ShaderSources_[name][0], ShaderSources_[name][1], ShaderSources_[name][2], macros);
    return Shaders[name].get();
}

Renderer::Shader* ResourceManager::GetShader(const std::string& name) {
    return GetShader(name.c_str());
}

Renderer::Shader* ResourceManager::GetShader(const char* name) {
    // TODO: check for existence
    return Shaders[name].get();
}

Renderer::Texture2D* ResourceManager::LoadTexture2D(const char* file, bool alpha, const std::string& name) {
    Textures[name] = std::unique_ptr<Renderer::Texture2D>(LoadTexture2DFromFile(file, alpha));
    return Textures[name].get();
}

Renderer::Texture2D* ResourceManager::LoadTexture2D(const std::string& file, bool alpha, const std::string& name) {
    return LoadTexture2D(file.c_str(), alpha, name);
}

Renderer::Texture2D* ResourceManager::GetTexture2D(std::string& name) {
    return GetTexture2D(name.c_str());
}

Renderer::Texture2D* ResourceManager::GetTexture2D(const char* name) {
    if (!Textures.contains(name)) {
        // checking if texture exists
        return nullptr;
    }
    return Textures[name].get();
}

glm::vec2 ResourceManager::GetSpriteSheetSize() {
    if (!Textures.contains(Constants::SPRITE_SHEET)) {
        // TODO: log message
        // sprite sheet was not loaded
        assert(false);
    }
    return {
        static_cast<float>(Textures[SpriteSheet.TextureName].get()->Width) / SpriteSheet.ItemWidth,
        static_cast<float>(Textures[SpriteSheet.TextureName].get()->Height) / SpriteSheet.ItemHeight
    };
}

void ResourceManager::Clear() {
    for (const auto& shader : Shaders | std::views::values) {
        glDeleteProgram(shader->Id);
    }
    for (const auto& texture : Textures | std::views::values) {
        glDeleteTextures(1, &texture->Id);
    }
}

std::unique_ptr<Renderer::Shader> ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile) {
    const std::string vertexCode = LoadShaderCodeFromFile(vShaderFile);
    const std::string fragmentCode = fShaderFile != nullptr ? LoadShaderCodeFromFile(fShaderFile) : "";
    const std::string geometryCode = gShaderFile != nullptr ? LoadShaderCodeFromFile(gShaderFile) : "";

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();

    auto shader = std::make_unique<Renderer::Shader>();
    shader->Compile(
      vShaderCode,
      fShaderFile != nullptr ? fShaderCode : nullptr,
      gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

std::unique_ptr<Renderer::Shader> ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const ShaderMacros_t& macros) {
    std::string vertexCode = LoadShaderCodeFromFile(vShaderFile);
    std::string fragmentCode = fShaderFile != nullptr ? LoadShaderCodeFromFile(fShaderFile) : "";
    std::string geometryCode = gShaderFile != nullptr ? LoadShaderCodeFromFile(gShaderFile) : "";

    auto shader = std::make_unique<Renderer::Shader>();
    shader->CompileWithMacros(std::move(vertexCode), std::move(fragmentCode), std::move(geometryCode), macros);
    return shader;
}

std::string ResourceManager::LoadShaderCodeFromFile(const char* shaderFile) {
    std::string code;
    try {
        std::ifstream source(shaderFile);
        std::stringstream shaderStream;
        shaderStream << source.rdbuf();
        source.close();
        code = shaderStream.str();
    }
    catch (std::exception&) {
        // TODO: handle failed load
        std::cout << "ERROR::SHADER: Failed to read shader file " << shaderFile << std::endl;
    }

    return code;
}

Renderer::Texture2D* ResourceManager::LoadTexture2DFromFile(const char* file, bool alpha) {
    // create texture object
    auto* texture = new Renderer::Texture2D;
    if (alpha) {
        texture->InternalFormat = GL_RGBA;
        texture->ImageFormat = GL_RGBA;
    }
    // load image
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (data) {
        // now generate texture
        texture->Generate(width, height, data);
    }
    else {
        // TODO: handle texture not loaded
        std::cout << "Failed to load texture" << std::endl;
    }
    // and finally free image data
    stbi_image_free(data);
    return texture;
}
