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
        glm::vec3 m_PointLightPositions[4];
        glm::vec3 m_PointLightColors[4];
        VertexArray m_ContainerVAO;
        VertexArray m_PointLightVAO;
        VertexBuffer m_CubeVBO;
        VertexBufferLayout m_CubeLayout;
        Texture m_DiffuseMap;
        Texture m_SpecularMap;
        Shader m_ContainerShader;
        Shader m_PointLightShader;
    };

}