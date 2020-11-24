#pragma once

#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "OrthographicCamera.h"

#include <memory>

namespace test {

    class TestBatchRendering final: public Test {
    public:
        TestBatchRendering();
        ~TestBatchRendering();

        void OnUpdate(float elapsedTime) override;
        void OnRender(const Camera &camera, float aspectRatio) override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<ElementBuffer> m_EBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_TextureA;
        std::unique_ptr<Texture> m_TextureB;
    };

}