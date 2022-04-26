#pragma once
#include <string>


namespace Constants {
const std::string SPRITE_SHEET = "sh";
const std::string SPRITE_SHEET_SPEC = "sh_s";
const std::string VOXEL_PACK_PATH_SH = "./res/textures/voxel-pack-updated/Spritesheets/";
constexpr auto FRAME_LEN = 1.0 / 60.0;

// render distance in chunks
constexpr int RENDERED_CHUNKS = 8;
// far plane of the frustum
constexpr float RENDER_DISTANCE = 200;
// far plane of the shadow frustum
constexpr float SHADOW_DISTANCE = 150;
constexpr int SHADOW_LEVELS = 3;
} // namespace Constants
