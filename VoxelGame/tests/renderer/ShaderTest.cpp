#include <iostream>

#include "../vendor/catch.hpp"

#include "renderer/Shader.h"

class ShaderTester : public Renderer::Shader {
  public:
    static bool ReplaceMacrosTest(std::string& source, const std::vector<std::pair<std::string, std::string>>& constants) {
        return ReplaceMacros(source, constants);
    }
};

bool ContainsLine(const std::string& str, const std::string& value) {
    std::istringstream in(str);

    for (std::string line; std::getline(in, line, '\n');) {
        if (line == value) {
            return true;
        }
    }

    return false;
}

TEST_CASE("Resource manager test", "[engine, ResourceManager]") {
    const std::string shaderSource = "#define CONS1 1.0\n#define CONS2 2.0\n#define CONS3 3.0\nvoid main() {}\n";

    SECTION("Replaces preprocessor macro") {
        std::string source(shaderSource);
        auto res = ShaderTester::ReplaceMacrosTest(
          source, { { "CONS1", "4" } });

        REQUIRE(res);
        REQUIRE(ContainsLine(source, "#define CONS1 4"));
        REQUIRE(ContainsLine(source, "#define CONS2 2.0"));
        REQUIRE(ContainsLine(source, "#define CONS3 3.0"));
        REQUIRE(ContainsLine(source, "void main() {}"));
    }

    SECTION("Replaces multiple preprocessor macros") {
        std::string source(shaderSource);
        auto res = ShaderTester::ReplaceMacrosTest(
          source, { { "CONS1", "4" }, { "CONS3", "5" } });

        REQUIRE(res);
        REQUIRE(ContainsLine(source, "#define CONS1 4"));
        REQUIRE(ContainsLine(source, "#define CONS2 2.0"));
        REQUIRE(ContainsLine(source, "#define CONS3 5"));
        REQUIRE(ContainsLine(source, "void main() {}"));
    }

    SECTION("Replaces no preprocessor macro") {
        std::string source(shaderSource);
        auto res = ShaderTester::ReplaceMacrosTest(
          source, { { "CONS", "4" } });

        REQUIRE_FALSE(res);
        REQUIRE(source == shaderSource);
    }
}
