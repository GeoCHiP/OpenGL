#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "OrthographicCamera.h"

#include <memory>

namespace test {

    class TestTriangle final: public Test {
    public:
        TestTriangle();
        ~TestTriangle() override;

        void OnUpdate(GLFWwindow *window, float elapsedTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        float m_Color[3];
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<OrthographicCamera> m_OrthoCamera;
    };

}