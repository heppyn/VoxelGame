#pragma once

#include "renderer/Texture2D.h"

namespace Renderer {
// framebuffer with attached dept component
class DepthMap {
  public:
    const int Width{ 4096 };
    const int Height{ 4096 };

    DepthMap() = default;
    DepthMap(int width, int height);
    void Init();
    void Bind() const;
    void BindTexture(unsigned slot = 0) const;

  private:
    unsigned FBO_{ 0 };
    Texture2D Texture_{};
};
} // namespace Renderer
