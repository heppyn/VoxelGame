#pragma once
#include <vector>
#include <string_view>
#include <fstream>

#include "LSystem.h"

namespace LSystems {
class LSystemParser {
public:
    [[nodiscard]] static std::vector<LSystem> LoadLSystemFromFile(const std::string_view file);

private:
    [[nodiscard]] static bool CheckIfProduction(std::ifstream& stream);
};
} // namespace LSystems
