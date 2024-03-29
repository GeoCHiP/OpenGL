#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Shader.h"
#include "PerspectiveCamera.h"

#include "glm/glm.hpp"

#include <memory>

namespace test {

    class TestMultipleLights final: public Test {
    public:
        TestMultipleLights();
        ~TestMultipleLights() override;

        void OnUpdate(GLFWwindow *window, float elapsedTime) override;
        void OnRender();
        void OnImGuiRender() override;

    private:
        glm::vec3 m_DirLightDirection;
        glm::vec3 m_DirLightAmbient;
        glm::vec3 m_DirLightDiffuse;
        glm::vec3 m_DirLightSpecular;
        glm::vec3 m_PointLightPositions[4];
        glm::vec3 m_PointLightAmbient[4];
        glm::vec3 m_PointLightDiffuse[4];
        glm::vec3 m_PointLightSpecular[4];
        float m_PointLightConstant[4];
        float m_PointLightLinear[4];
        float m_PointLightQuadratic[4];
        glm::vec3 m_SpotLightPosition;
        glm::vec3 m_SpotLightDirection;
        float m_SpotLightInnerCutOff;
        float m_SpotLightOuterCutOff;
        glm::vec3 m_SpotLightAmbient;
        glm::vec3 m_SpotLightDiffuse;
        glm::vec3 m_SpotLightSpecular;
        float m_SpotLightConstant;
        float m_SpotLightLinear;
        float m_SpotLightQuadratic;
        bool m_IsEnabledDirLight;
        bool m_IsEnabledPointLight;
        bool m_IsEnabledSpotLight;
        std::unique_ptr<VertexArray> m_ContainerVAO;
        std::unique_ptr<VertexArray> m_PointLightVAO;
        std::unique_ptr<VertexBuffer> m_CubeVBO;
        std::unique_ptr<VertexBufferLayout> m_CubeLayout;
        std::unique_ptr<Texture> m_DiffuseMap;
        std::unique_ptr<Texture> m_SpecularMap;
        std::unique_ptr<Shader> m_ContainerShader;
        std::unique_ptr<Shader> m_PointLightShader;
        std::unique_ptr<PerspectiveCamera> m_PerspectiveCamera;
    };

}