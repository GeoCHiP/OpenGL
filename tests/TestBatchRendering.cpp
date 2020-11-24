#include "TestBatchRendering.h"
#include "VertexBufferLayout.h"
#include "OrthographicCamera.h"

#include "GLFW/glfw3.h"

namespace test {

    TestBatchRendering::TestBatchRendering() {
        float vertices[] = {
            -1.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
            -1.5f,  0.5f, 0.0f,

             0.5f, -0.5f, 0.0f,
             1.5f, -0.5f, 0.0f,
             1.5f,  0.5f, 0.0f,
             0.5f,  0.5f, 0.0f
        };

        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4
        };

        m_VAO = std::make_unique<VertexArray>();
        m_VAO->Bind();

        m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        m_VAO->AddBuffer(*m_VBO, layout);

        m_EBO = std::make_unique<ElementBuffer>(indices, 12);

        m_VAO->Unbind();

        m_Shader = std::make_unique<Shader>("../resources/shaders/BatchRendering.glsl");
        m_TextureA = std::make_unique<Texture>("../resources/textures/logo.jpg");
        m_TextureB = std::make_unique<Texture>("../resources/textures/wooden_container.jpg");
    }

    TestBatchRendering::~TestBatchRendering() {}

    void TestBatchRendering::OnUpdate(float elapsedTime) {
        
    }

    void TestBatchRendering::OnRender(const Camera &camera, float aspectRatio) {
        const OrthographicCamera *orthoCamera = dynamic_cast<const OrthographicCamera*>(&camera);
        m_Shader->Bind();
        m_Shader->SetUniform1f("u_AspectRatio", aspectRatio);
        m_Shader->SetUniformMat4f("u_ViewProjection", orthoCamera->GetViewProjectionMatrix());
        Renderer renderer;
        renderer.DrawElements(*m_VAO, *m_EBO, *m_Shader);
    }

    void TestBatchRendering::OnImGuiRender() {}

}