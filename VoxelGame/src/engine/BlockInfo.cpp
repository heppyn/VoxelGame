#include "BlockInfo.h"

#include <cassert>

void BlockInfo::SetSurfaceHeight(float height) {
    assert(height >= 0);
    Info_ = (Info_ & 0xFFFF00) | static_cast<uint32_t>(height);
}

void BlockInfo::AddTree() {
    Info_ |= 0x800000;
}

void BlockInfo::SetBiome(unsigned int biome) {
    Info_ = (Info_ & 0xFFF8FF) | (biome << 8);
}
