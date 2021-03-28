#pragma once

#include <glad/glad.h>


class Texture2D {
  public:
    unsigned int m_id;
    unsigned int m_width{ 0 }, m_height{ 0 };
    unsigned int m_internalFormat{ GL_RGB };
    unsigned int m_imageFormat{ GL_RGB };

    unsigned int m_wrapS{ GL_REPEAT };
    unsigned int m_wrapT{ GL_REPEAT };
    unsigned int m_filterMin{ GL_LINEAR }; // filtering mode if texture pixels < screen pixels
    unsigned int m_filterMax{ GL_LINEAR }; // filtering mode if texture pixels > screen pixels

    Texture2D();
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind(unsigned int slot = 0) const;
};
