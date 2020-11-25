#include "TestBatchRendering.h"
#include "VertexBufferLayout.h"
#include "OrthographicCamera.h"

namespace test {

    TestBatchRendering::TestBatchRendering() {
        float vertices[] = {
            // Position         // TexCoord // Index
            -1.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
            -1.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,

             0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
             1.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
             1.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4
        };

        m_OrthoCamera = std::make_unique<OrthographicCamera>(-2.0f, 2.0f, -2.0f, 2.0f);

        m_VAO = std::make_unique<VertexArray>();
        m_VAO->Bind();

        m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        layout.Push<float>(1);
        m_VAO->AddBuffer(*m_VBO, layout);

        m_EBO = std::make_unique<ElementBuffer>(indices, 12);

        m_VAO->Unbind();

        m_Shader = std::make_unique<Shader>("../resources/shaders/BatchRendering.glsl");
        m_TextureA = std::make_unique<Texture>("../resources/textures/logo.jpg");
        m_TextureB = std::make_unique<Texture>("../resources/textures/wooden_container.jpg");
    }

    TestBatchRendering::~TestBatchRendering() {}

    void TestBatchRendering::OnUpdate(GLFWwindow *window, float elapsedTime) {
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

    void TestBatchRendering::OnRender() {
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_ViewProjection", m_OrthoCamera->GetViewProjectionMatrix());
        m_Shader->SetUniform1f("u_AspectRatio", m_OrthoCamera->GetAspectRatio());

        m_TextureA->Bind(0);
        m_TextureB->Bind(1);
        m_Shader->SetUniform1i("u_TextureA", 0);
        m_Shader->SetUniform1i("u_TextureB", 1);

        Renderer renderer;
        renderer.DrawElements(*m_VAO, *m_EBO, *m_Shader);
    }

    void TestBatchRendering::OnImGuiRender() {}

}