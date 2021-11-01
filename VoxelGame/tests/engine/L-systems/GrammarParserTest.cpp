#include "../../vendor/catch.hpp"

#include "engine/L-systems/GrammarParser.h"

TEST_CASE("grammar parser test", "[engine, grammarParser]") {
    SECTION("grammar can be loaded from file") {
        const auto grammar = LSystems::GrammarParser::LoadGrammarFromFile("./tests/engine/L-systems/grammar.txt");

        REQUIRE(grammar.size() == 1);
        REQUIRE(grammar[0].Derivate(0) == "X");
        REQUIRE(grammar[0].Derivate(1) == "U[&X][^X]UX");
        REQUIRE(grammar[0].Derivate(2) == "UU[&U[&X][^X]UX][^U[&X][^X]UX]UUU[&X][^X]UX");
    }

    SECTION("multiple grammars can be loaded from file") {
        const auto grammar = LSystems::GrammarParser::LoadGrammarFromFile("./tests/engine/L-systems/multipleGrammars.txt");

        REQUIRE(grammar.size() == 2);
        REQUIRE(grammar[1].Derivate(0) == "X");
        REQUIRE(grammar[1].Derivate(1) == "Y");
        REQUIRE(grammar[1].Derivate(2) == "Z");
        REQUIRE(grammar[1].Derivate(3) == "X");
    }
}
