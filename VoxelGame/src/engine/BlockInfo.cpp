#include "BlockInfo.h"

void BlockInfo::SetSurfaceHeight(float height) {
    Info_ = (Info_ & 0xFFFF00) | static_cast<uint32_t>(height);
}

void BlockInfo::AddTree() {
    Info_ |= 0x100;
}
