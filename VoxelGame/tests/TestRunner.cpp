#define CATCH_CONFIG_RUNNER
#define VXL_PROVIDED_TEST_RUNNER
#include "vendor/catch.hpp"

#include "engine/EntryPoint.h"

#include "engine/Game.h"


Game* Engine::CreateGame() {
    return new Game;
}

namespace Engine {
std::function<int()> GetTestRunner() {
    return []() {
        // first initialize game to use resource manager etc.
        // add -s to see successful runs
        // const char* params[] = { "main", "-s" };
        const int result = Catch::Session().run();
        if (result) {
            std::cin.ignore();
            return result;
        }
        #ifdef TEST_ONLY
        std::cin.ignore();
        return 1;
        #else
        return 0;
        #endif
    };
}
} // namespace Engine