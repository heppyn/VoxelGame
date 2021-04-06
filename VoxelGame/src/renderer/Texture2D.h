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
    unsigned int Width{ 0 }, Height{ 0 };
    unsigned int InternalFormat{ GL_RGB };
    unsigned int ImageFormat{ GL_RGB };

    unsigned int WrapS{ GL_REPEAT };
    unsigned int WrapT{ GL_REPEAT };
    unsigned int FilterMin{ GL_LINEAR }; // filtering mode if texture pixels < screen pixels
    unsigned int FilterMax{ GL_LINEAR }; // filtering mode if texture pixels > screen pixels

    Texture2D();
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind(unsigned int slot = 0) const;
};
} // namespace Renderer
