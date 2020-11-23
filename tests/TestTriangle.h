#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

namespace test {

    class TestTriangle final: public Test {
    public:
        TestTriangle();
        ~TestTriangle() override;

        void OnUpdate(float elapsedTime) override;
        void OnRender(const Camera &camera = Camera(), float aspectRatio = 4.0f / 3.0f) override;
        void OnImGuiRender() override;

    private:
        float m_Vertices[9];
        float m_Color[3];
        VertexArray m_VAO;
        VertexBuffer m_VBO;
        VertexBufferLayout m_Layout;
        Shader m_Shader;
    };

}