#include "TestRunner.h"

#include <iostream>
#include <vector>

#include "./engine/BlockInfoTest.h"


void Tests::TestRunner::RunTests() {
    std::cout << "Starting tests...\n";

    std::vector tests{
        BlockInfoTest(),
    };

    for (auto& test : tests) {
        test.RunTests();
    }

    std::cout << "All tests finished successfully\n";
}

