#include "TestTriangle.h"

#include "imgui/imgui.h"

namespace test {

    TestTriangle::TestTriangle()
    : m_Vertices {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    },
    m_Color { 0.2f, 0.3f, 0.8f } {
        m_VBO.AttachData(m_Vertices, sizeof(m_Vertices));
        m_Layout.Push<float>(3);
        m_VAO.AddBuffer(m_VBO, m_Layout);
        m_VAO.Unbind();
        m_Shader.LoadShader("../resources/shaders/TestTriangle.glsl");
    }

    TestTriangle::~TestTriangle() {}

    void TestTriangle::OnUpdate(float elapsedTime) {}

    void TestTriangle::OnRender(const Camera &camera, float aspectRatio) {
        m_VAO.Bind();
        m_Shader.Bind();
        m_Shader.SetUniform3f("u_Color", m_Color[0], m_Color[1], m_Color[2]);
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
    }

    void TestTriangle::OnImGuiRender() {
        ImGui::ColorEdit3("Color", m_Color);
    }

}