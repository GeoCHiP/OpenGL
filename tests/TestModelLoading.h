#pragma once

#include "Test.h"
#include "Model.h"
#include "Shader.h"

#include <memory>

namespace test {

    class TestModelLoading final: public Test {
    public:
        TestModelLoading();
        ~TestModelLoading();

        void OnUpdate(GLFWwindow *window, float elapsedTime);
        void OnRender();
        void OnImGuiRender();
    private:
        std::unique_ptr<Model> m_Model;
        std::unique_ptr<Shader> m_Shader;
    };

}