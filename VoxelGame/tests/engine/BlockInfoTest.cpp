#include "BlockInfoTest.h"

#include <cassert>
#include <iostream>

#include "engine/BlockInfo.h"
#include "helpers/Math.h"


void Tests::BlockInfoTest::RunTests() {
    TreeTest();
    HeightTest();

    std::cout << "Block Info tests OK\n";
}
void Tests::BlockInfoTest::TreeTest() {
    BlockInfo bi;
    assert(bi.HasTree() == false);

    bi.AddTree();
    assert(bi.HasTree() == true);
}

void Tests::BlockInfoTest::HeightTest() {
    BlockInfo bi;
    assert(Helpers::Math::Equal(bi.GetSurfaceHeight(), 0.0f));

    bi.SetSurfaceHeight(255.0f);
    assert(Helpers::Math::Equal(bi.GetSurfaceHeight(), 255.0f));

    bi.SetSurfaceHeight(5.0f);
    assert(Helpers::Math::Equal(bi.GetSurfaceHeight(), 5.0f));
}
