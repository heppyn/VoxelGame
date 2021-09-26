#include "BlockInfoTest.h"

#include <cassert>
#include <iostream>

#include "helpers/Math.h"


void Tests::BlockInfoTest::RunTests() {
    TreeTest();
    HeightTest();
    BiomeTest();

    std::cout << "Block Info tests OK\n";
}
void Tests::BlockInfoTest::TreeTest() {
    assert(BlockInfo_.HasTree() == false);

    BlockInfo_.AddTree();
    assert(BlockInfo_.HasTree() == true);
}

void Tests::BlockInfoTest::HeightTest() {
    assert(Helpers::Math::Equal(BlockInfo_.GetSurfaceHeight(), 0.0f));

    BlockInfo_.SetSurfaceHeight(255.0f);
    assert(Helpers::Math::Equal(BlockInfo_.GetSurfaceHeight(), 255.0f));

    BlockInfo_.SetSurfaceHeight(5.0f);
    assert(Helpers::Math::Equal(BlockInfo_.GetSurfaceHeight(), 5.0f));
}

void Tests::BlockInfoTest::BiomeTest() {
    assert(BlockInfo_.GetBiome() == 0u);

    BlockInfo_.SetBiome(1);
    assert(BlockInfo_.GetBiome() == 1u);

    BlockInfo_.SetBiome(7);
    assert(BlockInfo_.GetBiome() == 7u);

    BlockInfo_.SetBiome(5);
    assert(BlockInfo_.GetBiome() == 5u);
}
