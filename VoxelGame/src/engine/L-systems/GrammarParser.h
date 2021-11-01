#pragma once
#include <vector>
#include <string_view>
#include <fstream>

#include "RandomGrammar.h"

namespace LSystems {
class GrammarParser {
public:
    [[nodiscard]] static std::vector<Detail::RandomGrammar> LoadGrammarFromFile(const std::string_view file);

private:
    [[nodiscard]] static bool CheckIfProduction(std::ifstream& stream);
};
} // namespace LSystems
