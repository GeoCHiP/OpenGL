#include "TestMultipleLights.h"
#include "Renderer.h"
#include "PerspectiveCamera.h"

#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

    TestMultipleLights::TestMultipleLights()
    : m_DirLightDirection(glm::vec3(-1.2f, -1.0f, -2.0f)),
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
        float cubeVertices[] = {
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
        };
        m_PerspectiveCamera = std::make_unique<PerspectiveCamera>(glm::vec3(0.0f, 0.0f, 5.0f),
                glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 800.0f / 600.0f);
        m_ContainerVAO = std::make_unique<VertexArray>();
        m_PointLightVAO = std::make_unique<VertexArray>();
        m_CubeVBO = std::make_unique<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
        m_DiffuseMap = std::make_unique<Texture>("../resources/textures/container_diffuse_map.png");
        m_SpecularMap = std::make_unique<Texture>("../resources/textures/container_specular_map.png");
        m_ContainerShader = std::make_unique<Shader>("../resources/shaders/MultipleLights.glsl");
        m_PointLightShader = std::make_unique<Shader>("../resources/shaders/LightSource.glsl");
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);
        m_ContainerVAO->AddBuffer(*m_CubeVBO, layout);
        m_ContainerVAO->Unbind();

        m_PointLightVAO->AddBuffer(*m_CubeVBO, layout);
        m_PointLightVAO->Unbind();
    }

    TestMultipleLights::~TestMultipleLights() {}

    void TestMultipleLights::OnUpdate(GLFWwindow *window, float elapsedTime) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            m_PerspectiveCamera->ProcessKeyboard(CameraMovement::Forward, elapsedTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            m_PerspectiveCamera->ProcessKeyboard(CameraMovement::Backward, elapsedTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            m_PerspectiveCamera->ProcessKeyboard(CameraMovement::Leftward, elapsedTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            m_PerspectiveCamera->ProcessKeyboard(CameraMovement::Rightward, elapsedTime);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            m_PerspectiveCamera->ProcessKeyboard(CameraMovement::Upward, elapsedTime);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            m_PerspectiveCamera->ProcessKeyboard(CameraMovement::Downward, elapsedTime);

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        m_PerspectiveCamera->SetAspectRatio((float)width / height);

        static bool s_IsEnabledCursor = true;
        static bool s_IsFirstMouse = true;
        static float s_LastX, s_LastY;
        static double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        if (s_IsFirstMouse) {
            s_LastX = xPos;
            s_LastY = yPos;
            s_IsFirstMouse = false;
        }
        float xOffset = xPos - s_LastX;
        float yOffset = s_LastY - yPos;
        s_LastX = xPos;
        s_LastY = yPos;
        m_PerspectiveCamera->ProcessMouseMovement(xOffset, yOffset);
    }

    void TestMultipleLights::OnRender() {
        GLCall(glEnable(GL_DEPTH_TEST));

        glm::vec3 containerPositions[] = {
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
        };

        m_ContainerShader->Bind();
        const glm::vec3 &cameraPosition = m_PerspectiveCamera->GetPosition();
        const glm::vec3 &cameraDirection = m_PerspectiveCamera->GetFront();

        m_ContainerShader->SetUniform3f("u_ViewerPosition", cameraPosition);

        if (m_IsEnabledDirLight) {
            m_ContainerShader->SetUniform3f("u_DirLight.direction", m_DirLightDirection);
            m_ContainerShader->SetUniform3f("u_DirLight.ambient", m_DirLightAmbient);
            m_ContainerShader->SetUniform3f("u_DirLight.diffuse", m_DirLightDiffuse);
            m_ContainerShader->SetUniform3f("u_DirLight.specular", m_DirLightSpecular);
        } else {
            m_ContainerShader->SetUniform3f("u_DirLight.direction", glm::vec3(0.0f));
            m_ContainerShader->SetUniform3f("u_DirLight.ambient", glm::vec3(0.0f));
            m_ContainerShader->SetUniform3f("u_DirLight.diffuse", glm::vec3(0.0f));
            m_ContainerShader->SetUniform3f("u_DirLight.specular", glm::vec3(0.0f));
        }

        if (m_IsEnabledPointLight) {
            for (int i = 0; i < 4; ++i) {
                std::string idx = std::to_string(i);
                m_ContainerShader->SetUniform3f(("u_PointLights[" + idx + "].position").c_str(), m_PointLightPositions[i]);
                m_ContainerShader->SetUniform3f(("u_PointLights[" + idx + "].ambient").c_str(), m_PointLightAmbient[i]);
                m_ContainerShader->SetUniform3f(("u_PointLights[" + idx + "].diffuse").c_str(), m_PointLightDiffuse[i]);
                m_ContainerShader->SetUniform3f(("u_PointLights[" + idx + "].specular").c_str(), m_PointLightSpecular[i]);
                m_ContainerShader->SetUniform1f(("u_PointLights[" + idx + "].constant").c_str(), m_PointLightConstant[i]);
                m_ContainerShader->SetUniform1f(("u_PointLights[" + idx + "].linear").c_str(), m_PointLightLinear[i]);
                m_ContainerShader->SetUniform1f(("u_PointLights[" + idx + "].quadratic").c_str(), m_PointLightQuadratic[i]);
            }
        } else {
            for (int i = 0; i < 4; ++i) {
                std::string idx = std::to_string(i);
                m_ContainerShader->SetUniform3f(("u_PointLights[" + idx + "].position").c_str(), glm::vec3(0.0f));
                m_ContainerShader->SetUniform3f(("u_PointLights[" + idx + "].ambient").c_str(), glm::vec3(0.0f));
                m_ContainerShader->SetUniform3f(("u_PointLights[" + idx + "].diffuse").c_str(), glm::vec3(0.0f));
                m_ContainerShader->SetUniform3f(("u_PointLights[" + idx + "].specular").c_str(), glm::vec3(0.0f));
                m_ContainerShader->SetUniform1f(("u_PointLights[" + idx + "].constant").c_str(), 1.0f);
                m_ContainerShader->SetUniform1f(("u_PointLights[" + idx + "].linear").c_str(), 1.0f);
                m_ContainerShader->SetUniform1f(("u_PointLights[" + idx + "].quadratic").c_str(), 1.0f);
            }
        }

        if (m_IsEnabledSpotLight) {
            m_SpotLightPosition = cameraPosition;
            m_SpotLightDirection = cameraDirection;
            m_ContainerShader->SetUniform3f("u_SpotLight.position", m_SpotLightPosition);
            m_ContainerShader->SetUniform3f("u_SpotLight.direction", m_SpotLightDirection);
            m_ContainerShader->SetUniform1f("u_SpotLight.innerCutOff", m_SpotLightInnerCutOff);
            m_ContainerShader->SetUniform1f("u_SpotLight.outerCutOff", m_SpotLightOuterCutOff);
            m_ContainerShader->SetUniform3f("u_SpotLight.ambient", m_SpotLightAmbient);
            m_ContainerShader->SetUniform3f("u_SpotLight.diffuse", m_SpotLightDiffuse);
            m_ContainerShader->SetUniform3f("u_SpotLight.specular", m_SpotLightSpecular);
            m_ContainerShader->SetUniform1f("u_SpotLight.constant", m_SpotLightConstant);
            m_ContainerShader->SetUniform1f("u_SpotLight.linear", m_SpotLightLinear);
            m_ContainerShader->SetUniform1f("u_SpotLight.quadratic", m_SpotLightQuadratic);
        } else {
            m_SpotLightPosition = glm::vec3(0.0f);
            m_SpotLightDirection = glm::vec3(0.0f);
            m_ContainerShader->SetUniform3f("u_SpotLight.position", glm::vec3(0.0f));
            m_ContainerShader->SetUniform3f("u_SpotLight.direction", glm::vec3(0.0f));
            m_ContainerShader->SetUniform1f("u_SpotLight.innerCutOff", 90.0f);
            m_ContainerShader->SetUniform1f("u_SpotLight.outerCutOff", 90.0f);
            m_ContainerShader->SetUniform3f("u_SpotLight.ambient", glm::vec3(0.0f));
            m_ContainerShader->SetUniform3f("u_SpotLight.diffuse", glm::vec3(0.0f));
            m_ContainerShader->SetUniform3f("u_SpotLight.specular", glm::vec3(0.0f));
            m_ContainerShader->SetUniform1f("u_SpotLight.constant", 1.0f);
            m_ContainerShader->SetUniform1f("u_SpotLight.linear", 1.0f);
            m_ContainerShader->SetUniform1f("u_SpotLight.quadratic", 1.0f);
        }

        m_DiffuseMap->Bind(0);
        m_SpecularMap->Bind(1);
        m_ContainerShader->SetUniform1i("u_Material.diffuse", 0);
        m_ContainerShader->SetUniform1i("u_Material.specular", 1);
        m_ContainerShader->SetUniform1f("u_Material.shininess", 32.0f);

        const glm::mat4 &viewProjectionMatrix = m_PerspectiveCamera->GetViewProjectionMatrix();
        m_ContainerShader->SetUniformMat4f("u_ViewProjection", viewProjectionMatrix);

        Renderer renderer;
        for(unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, containerPositions[i]);
            float angle = 20.0f * i * (i % 2 ? glfwGetTime() : 1);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_ContainerShader->SetUniformMat4f("u_Model", model);

            renderer.DrawArrays(*m_ContainerVAO, *m_ContainerShader, 0, 36);
        }

        m_PointLightShader->Bind();
        m_PointLightShader->SetUniformMat4f("u_ViewProjection", viewProjectionMatrix);

        if (m_IsEnabledPointLight) {
            for (int i = 0; i < 4; ++i) {
                glm::mat4 model(1.0f);
                model = glm::translate(model, m_PointLightPositions[i]);
                model = glm::scale(model, glm::vec3(0.2f));
                m_PointLightShader->SetUniformMat4f("u_Model", model);
                glm::vec3 color = m_PointLightAmbient[i] + m_PointLightDiffuse[i] + m_PointLightSpecular[i];
                m_PointLightShader->SetUniform3f("u_Color", color);
                renderer.DrawArrays(*m_PointLightVAO, *m_PointLightShader, 0, 36);
            }
        }

        GLCall(glDisable(GL_DEPTH_TEST));
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