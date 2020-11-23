#pragma once

#include <vector>
#include <functional>
#include <string>
#include <iostream>

#include "Camera.h"

namespace test {

    class Test {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float elapsedTime) {}
        virtual void OnRender(const Camera &camera = Camera(), float aspectRatio = 4.0f / 3.0f) {}
        virtual void OnImGuiRender() {}
    };

    class TestMenu : public Test {
    public:
        TestMenu(Test *&currentTestPointer);
        ~TestMenu();

        void OnImGuiRender() override;

        template <typename T>
        void RegisterTest(const std::string &name) {
            std::cout << "Registered test \"" << name << "\"" << std::endl;
            m_Tests.push_back(std::make_pair(name, [](){ return new T(); }));
        }

    private:
        Test *&m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };

}