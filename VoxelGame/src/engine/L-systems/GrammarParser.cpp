#include "GrammarParser.h"

#include <iostream>

std::vector<LSystems::Detail::RandomGrammar> LSystems::GrammarParser::LoadGrammarFromFile(const std::string_view file) {
    std::vector<Detail::RandomGrammar> res;
    try {
        std::ifstream grammarFile(file.data());
        if (!grammarFile.is_open()) {
            std::cout << "File [" << file << "] could not be opened";
            return {};
        }

        float yaw, pitch;
        char letter;
        std::string axiom;

        while (!grammarFile.eof()) {
            if (!(grammarFile >> yaw >> pitch)) {
                // no other definition found - return current result
                break;
            }
            grammarFile >> axiom;
            auto grammar = Detail::RandomGrammar(axiom);

            while (grammarFile.good() && CheckIfProduction(grammarFile)) {
                std::string production;
                grammarFile >> letter;
                // skip arrow
                grammarFile.seekg(3, std::ios::cur);
                std::getline(grammarFile, production);

                grammar.AddProduction(letter, std::move(production));
            }

            res.emplace_back(std::move(grammar));
        }
    }
    catch (std::exception&) {
        std::cout << "Failed to load grammar from [" << file << "]\n";
        return {};
    }

    return res;
}

bool LSystems::GrammarParser::CheckIfProduction(std::ifstream& stream) {
    char dummy;
    // skip to potential axiom line
    stream >> dummy;
    stream.seekg(1, std::ios::cur);
    const auto production = stream.peek() == '>';
    stream.seekg(-2, std::ios::cur);

    return production;
}
