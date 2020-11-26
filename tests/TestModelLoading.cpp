#include "TestModelLoading.h"

#include "glm/gtc/matrix_transform.hpp"

namespace test {

    TestModelLoading::TestModelLoading() {
        m_PerspectiveCamera = std::make_unique<PerspectiveCamera>(glm::vec3(0.0f, 0.0f, 5.0f),
                glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 800.0f / 600.0f);
        m_Model = std::make_unique<Model>("../resources/models/backpack/backpack.obj");
        m_Shader = std::make_unique<Shader>("../resources/shaders/ModelLoading.glsl");
    }

    TestModelLoading::~TestModelLoading() {}

    void TestModelLoading::OnUpdate(GLFWwindow *window, float elapsedTime) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            m_PerspectiveCamera->ProcessKeyboard(CameraMovement::Forward, elapsedTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            m_PerspectiveCamera->ProcessKeyboard(CameraMovement::Backward, elapsedTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            m_PerspectiveCamera->ProcessKeyboard(CameraMovement::Leftward, elapsedTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            m_PerspectiveCamera->ProcessKeyboard(CameraMovement::Rightward, elapsedTime);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            m_PerspectiveCamera->ProcessKeyboard(CameraMovement::Upward, elapsedTime);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            m_PerspectiveCamera->ProcessKeyboard(CameraMovement::Downward, elapsedTime);

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        m_PerspectiveCamera->SetAspectRatio((float)width / height);

        static bool s_IsEnabledCursor = true;
        static bool s_IsFirstMouse = true;
        static float s_LastX, s_LastY;
        static double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        if (s_IsFirstMouse) {
            s_LastX = xPos;
            s_LastY = yPos;
            s_IsFirstMouse = false;
        }
        float xOffset = xPos - s_LastX;
        float yOffset = s_LastY - yPos;
        s_LastX = xPos;
        s_LastY = yPos;
        m_PerspectiveCamera->ProcessMouseMovement(xOffset, yOffset);
    }

    void TestModelLoading::OnRender() {
        glEnable(GL_DEPTH_TEST);
        glm::mat4 model(1.0f);
        model = glm::scale(model, glm::vec3(1.0f));
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_Model", model);
        m_Shader->SetUniformMat4f("u_ViewProjection", m_PerspectiveCamera->GetViewProjectionMatrix());
        m_Model->Draw(*m_Shader);
    }
    void TestModelLoading::OnImGuiRender() {}

}