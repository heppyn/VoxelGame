#pragma once
#include <cstdint>

class BlockInfo {
  private:
    /* from the most significant to the least significant
     * 1 bit - has a tree
     * 1 bit
     * 1 bit
     * 1 bit
     * 1 bit - humidity
     * 1 bit - humidity
     * 1 bit - humidity
     * 1 bit - humidity
     *
     * 1 bit - temperature
     * 1 bit - temperature
     * 1 bit - temperature
     * 1 bit - temperature
     * 1 bit - biome
     * 1 bit - biome
     * 1 bit - biome
     * 1 bit - biome
     *
     * 8 bits - height
     */
    uint32_t Info_{ 0 };

  public:
    [[nodiscard]] float GetSurfaceHeight() const { return static_cast<float>(Info_ & 0xFF); }
    [[nodiscard]] bool HasTree() const { return Info_ & 0x800000; }
    [[nodiscard]] unsigned GetBiome() const { return (Info_ >> 8) & 0xF; }
    [[nodiscard]] unsigned GetHumidity() const { return ( Info_ >> 16 ) & 0xF; }
    [[nodiscard]] unsigned GetTemperature() const { return ( Info_ >> 12 ) & 0xF; }

    void SetSurfaceHeight(float height);
    void AddTree();
    void SetBiome(unsigned biome);
    void SetHumidity(unsigned humidity);
    void SetTemperature(unsigned temperature);
};
