#pragma once

#include <string>
#include <glad/glad.h>


namespace Renderer {
class Texture2D {
  public:
    unsigned int Id{ 0 };
    // texture_diffuse, texture_specular, texture_normal, texture_height
    // default is diffuse
    std::string Type{ "texture_diffuse" };
    int Width{ 0 }, Height{ 0 };
    int InternalFormat{ GL_RGB };
    int ImageFormat{ GL_RGB };
    int DataType{ GL_UNSIGNED_BYTE };

    int WrapS{ GL_CLAMP_TO_EDGE }; // prevent colored bored on transparent textures
    int WrapT{ GL_CLAMP_TO_EDGE }; // only works in single texture
    // GL_NEAREST prevents lines around textures using sprite sheet
    int FilterMin{ GL_NEAREST }; // filtering mode if texture pixels < screen pixels
    int FilterMax{ GL_NEAREST }; // filtering mode if texture pixels > screen pixels

    Texture2D();
    void Generate(int width, int height, unsigned char* data);
    void Bind(unsigned int slot = 0) const;
    void SetTypeDiffuse();
    void SetTypeSpecular();
    void SetTypeNormal();
    void SetTypeHeight();
    void SetTypeShadow();
};
} // namespace Renderer
