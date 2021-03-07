#pragma once

#include <vector>
#include <string>
#include <functional>
#include <iostream>

namespace test {

	class Test {
	public:
		Test() = default;
		virtual ~Test() = default;

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override;
		template<typename T>
		void RegisterTest(const std::string& name) {
			std::cout << "Registering test " << name << std::endl;

			m_tests.push_back(std::make_pair(name, []() {return new T(); }));
		}
	private:
		Test* m_currentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_tests;
	};
}