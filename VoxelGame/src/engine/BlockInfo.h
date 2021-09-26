#pragma once
#include <cstdint>

class BlockInfo {
  private:
    /* from the most significant to the least significant
     * 1 bit - has a tree
     * 1 bit
     * 1 bit
     * 1 bit
     * 1 bit
     * 1 bit
     * 1 bit
     * 1 bit
     *
     * 1 bit
     * 1 bit
     * 1 bit
     * 1 bit
     * 1 bit
     * 1 bit - biome variation
     * 1 bit - biome variation
     * 1 bit - biome variation
     *
     * 8 bits - height
     */
    uint32_t Info_{ 0 };

  public:
    [[nodiscard]] float GetSurfaceHeight() const { return static_cast<float>(Info_ & 0xFF); }
    [[nodiscard]] bool HasTree() const { return Info_ & 0x800000; }
    [[nodiscard]] unsigned int GetBiome() const { return (Info_ >> 8) & 0x7; }

    void SetSurfaceHeight(float height);
    void AddTree();
    void SetBiome(unsigned int biome);
};
