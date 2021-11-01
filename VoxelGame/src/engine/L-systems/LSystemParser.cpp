#include "LSystemParser.h"

#include <iostream>

std::vector<LSystems::LSystem> LSystems::LSystemParser::LoadLSystemFromFile(const std::string_view file) {
    std::vector<LSystem> res;
    try {
        std::ifstream lSystemFile(file.data());
        if (!lSystemFile.is_open()) {
            std::cout << "File [" << file << "] could not be opened";
            return {};
        }

        float yaw, pitch, shrinkRatio;
        char letter;
        std::string axiom;

        while (!lSystemFile.eof()) {
            if (!(lSystemFile >> yaw >> pitch >> shrinkRatio)) {
                // no other definition found - return current result
                break;
            }
            lSystemFile >> axiom;
            auto grammar = Detail::RandomGrammar(axiom);

            while (lSystemFile.good() && CheckIfProduction(lSystemFile)) {
                std::string production;
                lSystemFile >> letter;
                // skip arrow
                lSystemFile.seekg(3, std::ios::cur);
                std::getline(lSystemFile, production);

                grammar.AddProduction(letter, std::move(production));
            }

            res.emplace_back(std::move(grammar), yaw, pitch, shrinkRatio);
        }
    }
    catch (std::exception&) {
        std::cout << "Failed to load L-system from [" << file << "]\n";
        return {};
    }

    return res;
}

bool LSystems::LSystemParser::CheckIfProduction(std::ifstream& stream) {
    char dummy;
    // skip to potential axiom line
    stream >> dummy;
    stream.seekg(1, std::ios::cur);
    const auto production = stream.peek() == '>';
    stream.seekg(-2, std::ios::cur);

    return production;
}
