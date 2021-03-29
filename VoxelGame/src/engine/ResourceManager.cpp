#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "stb_image/stb_image.h"

std::map<std::string, std::unique_ptr<Renderer::Shader>> ResourceManager::Shaders;
std::map<std::string, std::unique_ptr<Renderer::Texture2D>> ResourceManager::Textures;

Renderer::Shader* ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name) {
    Shaders[name] = std::unique_ptr<Renderer::Shader>(LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile));
    return Shaders[name].get();
}

Renderer::Shader* ResourceManager::GetShader(std::string& name) {
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

Renderer::Texture2D* ResourceManager::GetTexture2D(std::string& name) {
    return GetTexture2D(name.c_str());
}

Renderer::Texture2D* ResourceManager::GetTexture2D(const char* name) {
    // TODO: check for existence
    return Textures[name].get();
}

void ResourceManager::Clear() {
    for (const auto& [fst, shader] : Shaders) {
        glDeleteProgram(shader->Id);
    }
    for (const auto& [fst, texture] : Textures) {
        glDeleteTextures(1, &texture->Id);
    }
}

Renderer::Shader* ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile /*= nullptr*/) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr) {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception&) {
        // TODO: handle failed load
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    auto* shader = new Renderer::Shader;
    shader->Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
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
