#include "LSystemParser.h"

#include <iostream>

std::vector<LSystems::LSystem> LSystems::LSystemParser::LoadLSystemFromFile(const std::string_view file) {
    std::vector<LSystem> res;
    try {
        std::ifstream lSystemFile(file.data());
        if (!lSystemFile.is_open()) {
            std::cout << "ERROR: File [" << file << "] could not be opened";
            return {};
        }

        float yaw, pitch, shrinkRatio;
        char letter;
        std::string axiom;

        while (!lSystemFile.eof()) {
            SkipIfComment(lSystemFile);
            if (!(lSystemFile >> yaw >> pitch >> shrinkRatio)) {
                // no other definition found - return current result
                assert(!res.empty() && "No L-system loaded");
                break;
            }
            SkipIfComment(lSystemFile);
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
        std::cout << "ERROR: Failed to load L-system from [" << file << "]\n";
        return {};
    }

    if (res.empty()) {
        std::cout << "WARNING: L-system not loaded\n";
    }

    return res;
}

bool LSystems::LSystemParser::CheckIfProduction(std::ifstream& stream) {
    SkipIfComment(stream);
    char dummy;
    // skip to potential axiom line
    stream >> dummy;
    stream.seekg(1, std::ios::cur);
    const auto production = stream.peek() == '>';
    stream.seekg(-2, std::ios::cur);

    return production;
}

void LSystems::LSystemParser::SkipIfComment(std::ifstream& stream) {
    char dummy;
    stream >> dummy;
    if (dummy == '#') {
        std::string tmp;
        std::getline(stream, tmp);
        SkipIfComment(stream);
    }
    else {
        stream.seekg(-1, std::ios::cur);
    }
}
