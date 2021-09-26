#pragma once


namespace Tests {
class TestClass {
  public:
    TestClass() = default;
    virtual ~TestClass() = default;
    virtual void RunTests() = 0;
};

} // namespace Tests
