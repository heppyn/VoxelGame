#pragma once
#include "../TestClass.h"
#include "engine/BlockInfo.h"

namespace Tests {
class BlockInfoTest : public TestClass {
  public:
    void RunTests() override;

  private:
    BlockInfo BlockInfo_;

    void TreeTest();
    void HeightTest();
    void BiomeTest();
};
} // namespace Tests
