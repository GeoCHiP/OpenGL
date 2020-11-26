#pragma once

#include "Test.h"
#include "Model.h"
#include "Shader.h"
#include "PerspectiveCamera.h"

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
        std::unique_ptr<PerspectiveCamera> m_PerspectiveCamera;
        glm::vec3 m_PointLightPositions;
        glm::vec3 m_PointLightAmbient;
        glm::vec3 m_PointLightDiffuse;
        glm::vec3 m_PointLightSpecular;
        float m_PointLightConstant;
        float m_PointLightLinear;
        float m_PointLightQuadratic;
    };

}