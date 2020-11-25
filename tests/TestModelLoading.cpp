#include "TestModelLoading.h"

namespace test {

    TestModelLoading::TestModelLoading() {
        m_Model = std::make_unique<Model>("../resources/models/backpack/backpack.obj");
        m_Shader = std::make_unique<Shader>("../resources/shaders/TestModelLoading.glsl");
    }

    TestModelLoading::~TestModelLoading() {}

    void TestModelLoading::OnUpdate(GLFWwindow *window, float elapsedTime) {}
    void TestModelLoading::OnRender() {
        m_Model->Draw(*m_Shader);
    }
    void TestModelLoading::OnImGuiRender() {}

}