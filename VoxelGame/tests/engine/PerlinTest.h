#pragma once
#include "../TestClass.h"

namespace Tests {
class PerlinTest : public TestClass {
public:
	void RunTests() override;

private:
    void PrintTable();
};

} // namespace Tests
