#include "TestMultipleLights.h"
#include "Renderer.h"

#include "GLFW/glfw3.h"
#include "imgui/imgui.h"

namespace test {

    TestMultipleLights::TestMultipleLights()
    : m_CubeVertices {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    },
    m_ContainerPositions {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    },
    m_PointLightPositions {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    },
    m_PointLightColors {
        glm::vec3(0.2f, 0.3f, 0.8f),
        glm::vec3(0.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 0.0f)
    }
    {
        m_CubeVBO.AttachData(m_CubeVertices, sizeof(m_CubeVertices));
        m_DiffuseMap.LoadImage("../resources/textures/container_diffuse_map.png"),
        m_SpecularMap.LoadImage("../resources/textures/container_specualr_map.png");
        m_ContainerShader.LoadShader("../resources/shaders/MultipleLights.glsl");
        m_PointLightShader.LoadShader("../resources/shaders/LightSource.glsl");
        m_CubeLayout.Push<float>(3);
        m_CubeLayout.Push<float>(3);
        m_CubeLayout.Push<float>(2);
        m_ContainerVAO.AddBuffer(m_CubeVBO, m_CubeLayout);
        m_ContainerVAO.Unbind();

        m_PointLightVAO.AddBuffer(m_CubeVBO, m_CubeLayout);
        m_PointLightVAO.Unbind();
    }

    TestMultipleLights::~TestMultipleLights() {}

    void TestMultipleLights::OnUpdate(float elapsedTime) {}

    void TestMultipleLights::OnRender(const Camera &camera, float aspectRatio) {
        m_ContainerVAO.Bind();
        m_ContainerShader.Bind();
        const glm::vec3 &cameraPosition = camera.GetPosition();
        const glm::vec3 &cameraDirection = camera.GetFront();

        m_ContainerShader.SetUniform3f("u_ViewerPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);

        for (int i = 0; i < 4; ++i) {
            std::string idx = std::to_string(i);
            m_ContainerShader.SetUniform3f(("u_PointLights[" + idx + "].position").c_str(), m_PointLightPositions[i].x, m_PointLightPositions[i].y, m_PointLightPositions[i].z);
            m_ContainerShader.SetUniform3f(("u_PointLights[" + idx + "].ambient").c_str(), 0.1f, 0.1f, 0.1f);
            m_ContainerShader.SetUniform3f(("u_PointLights[" + idx + "].diffuse").c_str(), m_PointLightColors[i].r, m_PointLightColors[i].g, m_PointLightColors[i].b);
            m_ContainerShader.SetUniform3f(("u_PointLights[" + idx + "].specular").c_str(), m_PointLightColors[i].r, m_PointLightColors[i].g, m_PointLightColors[i].b);
            m_ContainerShader.SetUniform1f(("u_PointLights[" + idx + "].constant").c_str(), 1.0f);
            m_ContainerShader.SetUniform1f(("u_PointLights[" + idx + "].linear").c_str(), 0.09f);
            m_ContainerShader.SetUniform1f(("u_PointLights[" + idx + "].quadratic").c_str(), 0.032f);
        }

        m_ContainerShader.SetUniform3f("u_SpotLight.position", cameraPosition.x, cameraPosition.y, cameraPosition.z);
        m_ContainerShader.SetUniform3f("u_SpotLight.direction", cameraDirection.x, cameraDirection.y, cameraDirection.z);
        m_ContainerShader.SetUniform1f("u_SpotLight.innerCutOff", glm::cos(glm::radians(5.0f)));
        m_ContainerShader.SetUniform1f("u_SpotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        m_ContainerShader.SetUniform3f("u_SpotLight.ambient", 0.1f, 0.1f, 0.1f);
        m_ContainerShader.SetUniform3f("u_SpotLight.diffuse", 0.0f, 0.0f, 1.0f);
        m_ContainerShader.SetUniform3f("u_SpotLight.specular", 0.0f, 0.0f, 1.0f);
        m_ContainerShader.SetUniform1f("u_SpotLight.constant", 1.0f);
        m_ContainerShader.SetUniform1f("u_SpotLight.linear", 0.09f);
        m_ContainerShader.SetUniform1f("u_SpotLight.quadratic", 0.032f);

        m_DiffuseMap.Bind(0);
        m_SpecularMap.Bind(1);
        m_ContainerShader.SetUniform1i("u_Material.diffuse", 0);
        m_ContainerShader.SetUniform1i("u_Material.specular", 1);
        m_ContainerShader.SetUniform1f("u_Material.shininess", 32.0f);

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.GetFoV()), aspectRatio, 0.1f, 100.0f);
        m_ContainerShader.SetUniformMat4f("u_View", view);
        m_ContainerShader.SetUniformMat4f("u_Projection", projection);

        for(unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, m_ContainerPositions[i]);
            float angle = 20.0f * i * (i % 2 ? glfwGetTime() : 1);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_ContainerShader.SetUniformMat4f("u_Model", model);

            GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
        }

        m_PointLightVAO.Bind();
        m_PointLightShader.Bind();
        m_PointLightShader.SetUniformMat4f("u_View", view);
        m_PointLightShader.SetUniformMat4f("u_Projection", projection);

        for (int i = 0; i < 4; ++i) {
            glm::mat4 model(1.0f);
            model = glm::translate(model, m_PointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            m_PointLightShader.SetUniformMat4f("u_Model", model);
            m_PointLightShader.SetUniform3f("u_Color", m_PointLightColors[i].r, m_PointLightColors[i].g, m_PointLightColors[i].b);
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
        }
    }

    void TestMultipleLights::OnImGuiRender() {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        for (int i = 0; i < 4; ++i) {
            std::string idx = std::to_string(i + 1);
            if (ImGui::CollapsingHeader(("Point light " + idx).c_str())) {
                ImGui::SliderFloat3(("Position " + idx).c_str(), &m_PointLightPositions[i].x, -10.0f, 10.0f);
                ImGui::ColorEdit3(("Color " + idx).c_str(), &m_PointLightColors[i].r);
            }
        }
    }

}