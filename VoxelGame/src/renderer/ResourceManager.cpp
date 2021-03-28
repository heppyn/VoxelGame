#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "stb_image/stb_image.h"

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const std::string& name) {
    Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string& name) {
    // TODO: check for existence
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture2D(const char* file, bool alpha, const std::string& name) {
    Textures[name] = LoadTexture2DFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture2D(std::string& name) {
    // TODO: check for existence
    return Textures[name];
}

void ResourceManager::Clear() {
    for (const auto [fst, snd] : Shaders) {
        glDeleteProgram(snd.Id);
    }
    for (const auto [fst, snd] : Textures) {
        glDeleteTextures(1, &snd.Id);
    }
}

Shader ResourceManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile /*= nullptr*/) {
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
    catch (std::exception) {
        // TODO: handle failed load
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::LoadTexture2DFromFile(const char* file, bool alpha) {
    // create texture object
    Texture2D texture;
    if (alpha) {
        texture.InternalFormat = GL_RGBA;
        texture.ImageFormat = GL_RGBA;
    }
    // load image
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (data) {
        // now generate texture
        texture.Generate(width, height, data);
    }
    else {
        // TODO: handle texture not loaded
        std::cout << "Failed to load texture" << std::endl;
    }
    // and finally free image data
    stbi_image_free(data);
    return texture;
}
