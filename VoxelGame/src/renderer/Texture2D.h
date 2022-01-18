#pragma once

#include <string>
#include <glad/glad.h>


namespace Renderer {
class Texture2D {
  public:
    unsigned int Id_{ 0 };
    // texture_diffuse, texture_specular, texture_normal, texture_height
    // default is diffuse
    std::string Type_{ "texture_diffuse" };
    unsigned int Width_{ 0 }, Height_{ 0 };
    unsigned int InternalFormat_{ GL_RGB };
    unsigned int ImageFormat_{ GL_RGB };

    unsigned int WrapS_{ GL_CLAMP_TO_EDGE }; // prevent colored bored on transparent textures
    unsigned int WrapT_{ GL_CLAMP_TO_EDGE }; // only works in single texture
    // GL_NEAREST prevents lines around textures using sprite sheet
    unsigned int FilterMin_{ GL_NEAREST }; // filtering mode if texture pixels < screen pixels
    unsigned int FilterMax_{ GL_NEAREST }; // filtering mode if texture pixels > screen pixels

    Texture2D();
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind(unsigned int slot = 0) const;
    void SetTypeDiffuse();
    void SetTypeSpecular();
    void SetTypeNormal();
    void SetTypeHeight();
};
} // namespace Renderer
