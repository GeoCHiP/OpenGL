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
    m_DirLightDirection(glm::vec3(1.2f, 1.0f, 2.0f)),
    m_DirLightAmbient(glm::vec3(0.1f)),
    m_DirLightDiffuse(glm::vec3(0.5f)),
    m_DirLightSpecular(glm::vec3(0.5f)),
    m_PointLightPositions {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    },
    m_PointLightAmbient {
        glm::vec3(0.1f),
        glm::vec3(0.1f),
        glm::vec3(0.1f),
        glm::vec3(0.1f)
    },
    m_PointLightDiffuse {
        glm::vec3(0.2f, 0.3f, 0.8f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 0.0f, 1.0f)
    },
    m_PointLightSpecular {
        glm::vec3(0.2f, 0.3f, 0.8f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 0.0f, 1.0f)
    },
    m_PointLightConstant { 1.0f, 1.0f, 1.0f, 1.0f },
    m_PointLightLinear {0.09f, 0.09f, 0.09f, 0.09f},
    m_PointLightQuadratic {0.032f, 0.032f, 0.032f, 0.032f},
    m_SpotLightPosition(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_SpotLightDirection(glm::vec3(0.0f, -1.0f, 0.0f)),
    m_SpotLightInnerCutOff(glm::cos(glm::radians(10.0f))),
    m_SpotLightOuterCutOff(glm::cos(glm::radians(17.5f))),
    m_SpotLightAmbient(glm::vec3(0.1f)),
    m_SpotLightDiffuse(glm::vec3(1.0f)),
    m_SpotLightSpecular(glm::vec3(1.0f)),
    m_SpotLightConstant(1.0f),
    m_SpotLightLinear(0.09f),
    m_SpotLightQuadratic(0.032),
    m_IsEnabledDirLight(false),
    m_IsEnabledPointLight(true),
    m_IsEnabledSpotLight(true) {
        m_CubeVBO.AttachData(m_CubeVertices, sizeof(m_CubeVertices));
        m_DiffuseMap.LoadImage("../resources/textures/container_diffuse_map.png"),
        m_SpecularMap.LoadImage("../resources/textures/container_specular_map.png");
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

        if (m_IsEnabledDirLight) {
            m_ContainerShader.SetUniform3f("u_DirLight.direction", m_DirLightDirection.x, m_DirLightDirection.y, m_DirLightDirection.z);
            m_ContainerShader.SetUniform3f("u_DirLight.ambient", m_DirLightAmbient.r, m_DirLightAmbient.g, m_DirLightAmbient.b);
            m_ContainerShader.SetUniform3f("u_DirLight.diffuse", m_DirLightDiffuse.r, m_DirLightDiffuse.g, m_DirLightDiffuse.b);
            m_ContainerShader.SetUniform3f("u_DirLight.specular", m_DirLightSpecular.r, m_DirLightSpecular.g, m_DirLightSpecular.b);
        } else {
            m_ContainerShader.SetUniform3f("u_DirLight.direction", 0.0f, 0.0f, 0.0f);
            m_ContainerShader.SetUniform3f("u_DirLight.ambient", 0.0f, 0.0f, 0.0f);
            m_ContainerShader.SetUniform3f("u_DirLight.diffuse", 0.0f, 0.0f, 0.0f);
            m_ContainerShader.SetUniform3f("u_DirLight.specular", 0.0f, 0.0f, 0.0f);
        }

        if (m_IsEnabledPointLight) {
            for (int i = 0; i < 4; ++i) {
                std::string idx = std::to_string(i);
                m_ContainerShader.SetUniform3f(("u_PointLights[" + idx + "].position").c_str(), m_PointLightPositions[i].x, m_PointLightPositions[i].y, m_PointLightPositions[i].z);
                m_ContainerShader.SetUniform3f(("u_PointLights[" + idx + "].ambient").c_str(), m_PointLightAmbient[i].r, m_PointLightAmbient[i].g, m_PointLightAmbient[i].b);
                m_ContainerShader.SetUniform3f(("u_PointLights[" + idx + "].diffuse").c_str(), m_PointLightDiffuse[i].r, m_PointLightDiffuse[i].g, m_PointLightDiffuse[i].b);
                m_ContainerShader.SetUniform3f(("u_PointLights[" + idx + "].specular").c_str(), m_PointLightSpecular[i].r, m_PointLightSpecular[i].g, m_PointLightSpecular[i].b);
                m_ContainerShader.SetUniform1f(("u_PointLights[" + idx + "].constant").c_str(), m_PointLightConstant[i]);
                m_ContainerShader.SetUniform1f(("u_PointLights[" + idx + "].linear").c_str(), m_PointLightLinear[i]);
                m_ContainerShader.SetUniform1f(("u_PointLights[" + idx + "].quadratic").c_str(), m_PointLightQuadratic[i]);
            }
        } else {
            for (int i = 0; i < 4; ++i) {
                std::string idx = std::to_string(i);
                m_ContainerShader.SetUniform3f(("u_PointLights[" + idx + "].position").c_str(), 0.0f, 0.0f, 0.0f);
                m_ContainerShader.SetUniform3f(("u_PointLights[" + idx + "].ambient").c_str(), 0.0f, 0.0f, 0.0f);
                m_ContainerShader.SetUniform3f(("u_PointLights[" + idx + "].diffuse").c_str(), 0.0f, 0.0f, 0.0f);
                m_ContainerShader.SetUniform3f(("u_PointLights[" + idx + "].specular").c_str(), 0.0f, 0.0f, 0.0f);
                m_ContainerShader.SetUniform1f(("u_PointLights[" + idx + "].constant").c_str(), 1.0f);
                m_ContainerShader.SetUniform1f(("u_PointLights[" + idx + "].linear").c_str(), 1.0f);
                m_ContainerShader.SetUniform1f(("u_PointLights[" + idx + "].quadratic").c_str(), 1.0f);
            }
        }

        if (m_IsEnabledSpotLight) {
            m_SpotLightPosition = cameraPosition;
            m_SpotLightDirection = cameraDirection;
            m_ContainerShader.SetUniform3f("u_SpotLight.position", m_SpotLightPosition.x, m_SpotLightPosition.y, m_SpotLightPosition.z);
            m_ContainerShader.SetUniform3f("u_SpotLight.direction", m_SpotLightDirection.x, m_SpotLightDirection.y, m_SpotLightDirection.z);
            m_ContainerShader.SetUniform1f("u_SpotLight.innerCutOff", m_SpotLightInnerCutOff);
            m_ContainerShader.SetUniform1f("u_SpotLight.outerCutOff", m_SpotLightOuterCutOff);
            m_ContainerShader.SetUniform3f("u_SpotLight.ambient", m_SpotLightAmbient.r, m_SpotLightAmbient.g, m_SpotLightAmbient.b);
            m_ContainerShader.SetUniform3f("u_SpotLight.diffuse", m_SpotLightDiffuse.r, m_SpotLightDiffuse.g, m_SpotLightDiffuse.b);
            m_ContainerShader.SetUniform3f("u_SpotLight.specular", m_SpotLightSpecular.r, m_SpotLightSpecular.g, m_SpotLightSpecular.b);
            m_ContainerShader.SetUniform1f("u_SpotLight.constant", m_SpotLightConstant);
            m_ContainerShader.SetUniform1f("u_SpotLight.linear", m_SpotLightLinear);
            m_ContainerShader.SetUniform1f("u_SpotLight.quadratic", m_SpotLightQuadratic);
        } else {
            m_SpotLightPosition = glm::vec3(0.0f);
            m_SpotLightDirection = glm::vec3(0.0f);
            m_ContainerShader.SetUniform3f("u_SpotLight.position", 0.0f, 0.0f, 0.0f);
            m_ContainerShader.SetUniform3f("u_SpotLight.direction", 0.0f, 0.0f, 0.0f);
            m_ContainerShader.SetUniform1f("u_SpotLight.innerCutOff", 90.0f);
            m_ContainerShader.SetUniform1f("u_SpotLight.outerCutOff", 90.0f);
            m_ContainerShader.SetUniform3f("u_SpotLight.ambient", 0.0f, 0.0f, 0.0f);
            m_ContainerShader.SetUniform3f("u_SpotLight.diffuse", 0.0f, 0.0f, 0.0f);
            m_ContainerShader.SetUniform3f("u_SpotLight.specular", 0.0f, 0.0f, 0.0f);
            m_ContainerShader.SetUniform1f("u_SpotLight.constant", 1.0f);
            m_ContainerShader.SetUniform1f("u_SpotLight.linear", 1.0f);
            m_ContainerShader.SetUniform1f("u_SpotLight.quadratic", 1.0f);
        }

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

        if (m_IsEnabledPointLight) {
            for (int i = 0; i < 4; ++i) {
                glm::mat4 model(1.0f);
                model = glm::translate(model, m_PointLightPositions[i]);
                model = glm::scale(model, glm::vec3(0.2f));
                m_PointLightShader.SetUniformMat4f("u_Model", model);
                glm::vec3 color = m_PointLightAmbient[i] + m_PointLightDiffuse[i] + m_PointLightSpecular[i];
                m_PointLightShader.SetUniform3f("u_Color", color.r, color.g, color.b);
                GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
            }
        }
    }

    void TestMultipleLights::OnImGuiRender() {
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        if (ImGui::IsItemHovered()) {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted("Press LEFT ALT to disable/enable the cursor.\nPress F11 to toggle fullscreen mode.\n");
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
        if (ImGui::CollapsingHeader("Directional Light")) {
            ImGui::Checkbox("Enabled", &m_IsEnabledDirLight);
            ImGui::SliderFloat3("Direction", &m_DirLightDirection.x, -5.0f, 5.0f);
            ImGui::ColorEdit3("Ambient", &m_DirLightAmbient.r);
            ImGui::ColorEdit3("Diffuse", &m_DirLightDiffuse.r);
            ImGui::ColorEdit3("Specular", &m_DirLightSpecular.r);
        }
        if (ImGui::CollapsingHeader("Point Light")) {
            ImGui::Checkbox("Enabled", &m_IsEnabledPointLight);
            for (int i = 0; i < 4; ++i) {
                std::string idx = std::to_string(i + 1);
                if (ImGui::TreeNode(("Point light " + idx).c_str())) {
                    ImGui::SliderFloat3(("Position " + idx).c_str(), &m_PointLightPositions[i].x, -10.0f, 10.0f);
                    ImGui::ColorEdit3("Ambient", &m_PointLightAmbient[i].r);
                    ImGui::ColorEdit3("Difuse", &m_PointLightDiffuse[i].r);
                    ImGui::ColorEdit3("Specular", &m_PointLightSpecular[i].r);
                    ImGui::SliderFloat("Constant", &m_PointLightConstant[i], 0.0f, 1.0f);
                    ImGui::SliderFloat("Linear", &m_PointLightLinear[i], 0.0f, 1.0f);
                    ImGui::SliderFloat("Quadratic", &m_PointLightQuadratic[i], 0.0f, 1.0f);
                    ImGui::TreePop();
                }
            }
        }
        if (ImGui::CollapsingHeader("Spot Light")) {
            ImGui::Checkbox("Enabled", &m_IsEnabledSpotLight);
            ImGui::SliderFloat3("Position", &m_SpotLightPosition.x, -10.f, 10.0f);
            ImGui::SliderFloat3("Direction", &m_SpotLightDirection.x, -10.0f, 10.0f);
            ImGui::SliderFloat("Inner cut off", &m_SpotLightInnerCutOff, glm::cos(glm::radians(0.0f)), glm::cos(glm::radians(90.0f)));
            ImGui::SliderFloat("Outer cut off", &m_SpotLightOuterCutOff, glm::cos(glm::radians(0.0f)), glm::cos(glm::radians(90.0f)));
            ImGui::ColorEdit3("Ambient", &m_SpotLightAmbient.r);
            ImGui::ColorEdit3("Diffuse", &m_SpotLightDiffuse.r);
            ImGui::ColorEdit3("Specular", &m_SpotLightSpecular.r);
            ImGui::SliderFloat("Constant", &m_SpotLightConstant, 0.0f, 1.0f);
            ImGui::SliderFloat("Linear", &m_SpotLightLinear, 0.0f, 1.0f);
            ImGui::SliderFloat("Quadratic", &m_SpotLightQuadratic, 0.0f, 1.0f);
        }
    }

}