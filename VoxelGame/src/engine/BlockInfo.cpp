#include "BlockInfo.h"

#include <cassert>

void BlockInfo::SetSurfaceHeight(float height) {
    assert(height >= 0);
    Info_ = (Info_ & 0xFFFF00) | static_cast<uint32_t>(height);
}

void BlockInfo::AddTree() {
    Info_ |= 0x800000;
}

void BlockInfo::SetBiome(unsigned biome) {
    assert(biome < 16);
    Info_ = (Info_ & 0xFFF0FF) | (biome << 8);
}

void BlockInfo::SetHumidity(unsigned humidity) {
    assert(humidity < 16);
    Info_ = (Info_ & 0xF0FFFF) | (humidity << 16);
}
void BlockInfo::SetTemperature(unsigned temperature) {
    assert(temperature < 16);
    Info_ = (Info_ & 0xFF0FFF) | (temperature << 12);
}
