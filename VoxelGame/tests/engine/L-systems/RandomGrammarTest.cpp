#include "../../vendor/catch.hpp"

#include "engine/L-systems/RandomGrammar.h"

TEST_CASE("grammar test", "[engine, grammar]") {
    SECTION("grammar can be derivated") {
        LSystems::Detail::RandomGrammar grammar("b");
        grammar.AddProduction('b', "a");
        grammar.AddProduction('a', "ab");

        REQUIRE(grammar.Derivate(1) == "a");
        REQUIRE(grammar.Derivate(2) == "ab");
        REQUIRE(grammar.Derivate(3) == "aba");
        REQUIRE(grammar.Derivate(4) == "abaab");
        REQUIRE(grammar.Derivate(5) == "abaababa");
    }

    SECTION("grammar can be derivated - more rules") {
        LSystems::Detail::RandomGrammar grammar("a");
        grammar.AddProduction('a', "bc");
        grammar.AddProduction('b', "da");
        grammar.AddProduction('c', "a");
        grammar.AddProduction('d', "b");

        REQUIRE(grammar.Derivate(0) == "a");
        REQUIRE(grammar.Derivate(1) == "bc");
        REQUIRE(grammar.Derivate(2) == "daa");
        REQUIRE(grammar.Derivate(3) == "bbcbc");
        REQUIRE(grammar.Derivate(4) == "dadaadaa");
    }

    SECTION("grammar can have random productions") {
        LSystems::Detail::RandomGrammar grammar("a");
        grammar.AddProduction('a', "ab");
        grammar.AddProduction('a', "c");

        const auto d1 = grammar.Derivate(1);
        INFO("derivation " <<  d1);
        REQUIRE((d1 == "c" || d1 == "ab"));

        const auto d2 = grammar.Derivate(2);
        INFO("derivation " <<  d2);
        REQUIRE((d2 == "c" || d2 == "cb" || d2 == "abb"));
    }
}