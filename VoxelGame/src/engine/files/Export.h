#pragma once

#include <fstream>

#include "engine/Scene.h"

namespace Engine::Files {
class Export {
  public:
    static void ExportScene(const Scene& scene, const std::string& fileName);
    static void ExportChunk(std::ofstream& stream, const Chunk& chunk);
};
} // namespace Engine::Files
