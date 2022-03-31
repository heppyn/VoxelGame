#include "Texture2D.h"

Renderer::Texture2D::Texture2D() {
    glGenTextures(1, &Id);
}

void Renderer::Texture2D::Generate(int width, int height, unsigned char* data) {
    Width = width;
    Height = height;

    glBindTexture(GL_TEXTURE_2D, Id);
    glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, Width, Height, 0, ImageFormat, DataType, data);

    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMax);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Renderer::Texture2D::Bind(unsigned int slot /*= 0 */) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, Id);
}

void Renderer::Texture2D::Delete() {
    glDeleteTextures(1, &Id);
    Id = 0;
}

void Renderer::Texture2D::SetAlpha() {
    InternalFormat = GL_RGBA;
    ImageFormat = GL_RGBA;
}

void Renderer::Texture2D::SetTypeDiffuse() {
    Type = "texture_diffuse";
}

void Renderer::Texture2D::SetTypeSpecular() {
    Type = "texture_specular";
}

void Renderer::Texture2D::SetTypeNormal() {
    Type = "texture_normal";
}

void Renderer::Texture2D::SetTypeHeight() {
    Type = "texture_height";
}

void Renderer::Texture2D::SetTypeShadow() {
    Type = "texture_shadow";
}
