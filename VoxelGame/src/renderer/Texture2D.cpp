#include "Texture2D.h"

Texture2D::Texture2D() {
    glGenTextures(1, &m_id);
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data) {
    m_width = width;
    m_height = height;

    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_imageFormat, GL_UNSIGNED_BYTE, data);

    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter_max);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture2D::Bind(unsigned int slot /* = 0 */) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}
