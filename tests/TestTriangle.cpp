#include "TestTriangle.h"
#include "VertexBufferLayout.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"

namespace test {

    TestTriangle::TestTriangle()
    : m_Color { 0.2f, 0.3f, 0.8f } {
        m_OrthoCamera = std::make_unique<OrthographicCamera>(-2.0f, 2.0f, -2.0f, 2.0f);
        float vertices[] {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };
        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        m_VAO->AddBuffer(*m_VBO, layout);
        m_VAO->Unbind();
        m_Shader = std::make_unique<Shader>("../resources/shaders/TestTriangle.glsl");
    }

    TestTriangle::~TestTriangle() {}

    void TestTriangle::OnUpdate(GLFWwindow *window, float elapsedTime) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            m_OrthoCamera->ProcessKeyboard(CameraMovement::Upward, elapsedTime);

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            m_OrthoCamera->ProcessKeyboard(CameraMovement::Downward, elapsedTime);

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
          m_OrthoCamera->ProcessKeyboard(CameraMovement::Leftward, elapsedTime);

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            m_OrthoCamera->ProcessKeyboard(CameraMovement::Rightward, elapsedTime);
        
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        m_OrthoCamera->SetAspectRatio((float)width / height);
    }

    void TestTriangle::OnRender() {
        Renderer renderer;
        m_Shader->Bind();
        m_Shader->SetUniform3f("u_Color", glm::vec3(m_Color[0], m_Color[1], m_Color[2]));
        m_Shader->SetUniform1f("u_AspectRatio", m_OrthoCamera->GetAspectRatio());
        m_Shader->SetUniformMat4f("u_ViewProjection", m_OrthoCamera->GetViewProjectionMatrix());
        renderer.DrawArrays(*m_VAO, *m_Shader, 0, 3);
    }

    void TestTriangle::OnImGuiRender() {
        ImGui::ColorEdit3("Color", m_Color);
    }

}