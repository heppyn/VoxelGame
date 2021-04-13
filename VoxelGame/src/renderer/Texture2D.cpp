#include "Texture2D.h"

Renderer::Texture2D::Texture2D() {
    glGenTextures(1, &Id_);
}

void Renderer::Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data) {
    Width_ = width;
    Height_ = height;

    glBindTexture(GL_TEXTURE_2D, Id_);
    glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat_, Width_, Height_, 0, ImageFormat_, GL_UNSIGNED_BYTE, data);

    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapS_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapT_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMin_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMax_);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Renderer::Texture2D::Bind(unsigned int slot /*= 0 */) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, Id_);
}

void Renderer::Texture2D::SetTypeDiffuse() {
    Type_ = "texture_diffuse";
}

void Renderer::Texture2D::SetTypeSpecular() {
    Type_ = "texture_specular";
}

void Renderer::Texture2D::SetTypeNormal() {
    Type_ = "texture_normal";
}

void Renderer::Texture2D::SetTypeHeight() {
    Type_ = "texture_height";
}
