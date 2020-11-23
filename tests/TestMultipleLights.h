#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"

#include "glm/glm.hpp"

namespace test {

    class TestMultipleLights final: public Test {
    public:
        TestMultipleLights();
        ~TestMultipleLights() override;

        void OnUpdate(float elapsedTime) override;
        void OnRender(const Camera &camera, float aspectRatio);
        void OnImGuiRender() override;

    private:
        float m_CubeVertices[288];
        glm::vec3 m_ContainerPositions[10];
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
        VertexArray m_ContainerVAO;
        VertexArray m_PointLightVAO;
        VertexBuffer m_CubeVBO;
        VertexBufferLayout m_CubeLayout;
        Texture m_DiffuseMap;
        Texture m_SpecularMap;
        Shader m_ContainerShader;
        Shader m_PointLightShader;
        bool m_IsEnabledDirLight;
        bool m_IsEnabledPointLight;
        bool m_IsEnabledSpotLight;
    };

}