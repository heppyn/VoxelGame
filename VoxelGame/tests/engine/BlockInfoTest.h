#pragma once
#include "../TestClass.h"

namespace Tests {
class BlockInfoTest : public TestClass {
  public:
    void RunTests() override;

  private:
    static void TreeTest();
    static void HeightTest();
};
} // namespace Tests
