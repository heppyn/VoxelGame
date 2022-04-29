#include "LSystemParser.h"

#include <iostream>
#include <fstream>

std::vector<LSystems::LSystem> LSystems::LSystemParser::LoadLSystemFromFile(const std::string_view file) {
    std::vector<LSystem> res;
    try {
        std::ifstream lSystemFile(file.data());
        if (!lSystemFile.is_open()) {
            std::cout << "ERROR: File [" << file << "] could not be opened\n";
            return {};
        }

        std::stringstream stream;
        const auto pos = lSystemFile.tellg();
        stream << lSystemFile.rdbuf();
        stream.seekg(pos);

        res = LoadLSystem(stream);
    }
    catch (std::exception&) {
        std::cout << "ERROR: Failed to load L-system from [" << file << "]\n";
        return {};
    }

    if (res.empty()) {
        std::cout << "WARNING: No L-system loaded from file [" << file << "]\n";
    }

    return res;
}

std::vector<LSystems::LSystem> LSystems::LSystemParser::LoadLSystem(std::string&& lSystems) {
    std::stringstream stream(lSystems);

    return LoadLSystem(stream);
}

std::vector<LSystems::LSystem> LSystems::LSystemParser::LoadLSystem(std::stringstream& stream) {
    std::vector<LSystem> res;
    float yaw, pitch, shrinkRatio;
    char letter;
    std::string axiom;

    while (!stream.eof()) {
        SkipIfComment(stream);
        if (!(stream >> yaw >> pitch >> shrinkRatio)) {
            // no other definition found - return current result
            assert(!res.empty() && "No L-system loaded");
            break;
        }
        SkipIfComment(stream);
        stream >> axiom;
        auto grammar = Detail::RandomGrammar(axiom);

        while (stream.good() && CheckIfProduction(stream)) {
            std::string production;
            stream >> letter;
            // skip arrow
            stream.seekg(3, std::ios::cur);
            std::getline(stream, production);

            grammar.AddProduction(letter, std::move(production));
        }

        res.emplace_back(std::move(grammar), yaw, pitch, shrinkRatio);
    }

    return res;
}

bool LSystems::LSystemParser::CheckIfProduction(std::stringstream& stream) {
    SkipIfComment(stream);
    char dummy;
    // skip to potential axiom line
    stream >> dummy;
    stream.seekg(1, std::ios::cur);
    const auto production = stream.peek() == '>';
    stream.seekg(-2, std::ios::cur);

    return production;
}

void LSystems::LSystemParser::SkipIfComment(std::stringstream& stream) {
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
