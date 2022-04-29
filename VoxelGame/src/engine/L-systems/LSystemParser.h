#pragma once
#include <vector>
#include <string_view>
#include <sstream>

#include "LSystem.h"

namespace LSystems {
/**
 * \brief Loads L-system from file/string
 */
class LSystemParser {
  public:
    [[nodiscard]] static std::vector<LSystem> LoadLSystemFromFile(const std::string_view file);
    [[nodiscard]] static std::vector<LSystem> LoadLSystem(std::string&& lSystems);
    [[nodiscard]] static std::vector<LSystem> LoadLSystem(std::stringstream& stream);

  private:
    [[nodiscard]] static bool CheckIfProduction(std::stringstream& stream);
    static void SkipIfComment(std::stringstream& stream);
};
} // namespace LSystems
