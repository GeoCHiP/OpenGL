#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


static Camera s_Camera(glm::vec3(0.0f, 0.0f, 5.0f));

static float s_Width = 800.0f;
static float s_Height = 600.0f;
static bool s_IsFoolScreen = false;
static bool s_EnableCursor = false;

static bool s_FirstMouse = true;
static float s_LastX = s_Width / 2;
static float s_LastY = s_Height / 2;

static float s_ElapsedTime = 0.0f;
static float s_LastFrame = 0.0f;


static void ProcessInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        s_Camera.ProcessKeyboard(CameraMovement::Forward, s_ElapsedTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        s_Camera.ProcessKeyboard(CameraMovement::Backward, s_ElapsedTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        s_Camera.ProcessKeyboard(CameraMovement::Leftward, s_ElapsedTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        s_Camera.ProcessKeyboard(CameraMovement::Rightward, s_ElapsedTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        s_Camera.ProcessKeyboard(CameraMovement::Upward, s_ElapsedTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        s_Camera.ProcessKeyboard(CameraMovement::Downward, s_ElapsedTime);
}

static void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    GLCall(glViewport(0, 0, width, height));
    s_Width = width;
    s_Height = height;
}

static void MouseMoveCallback(GLFWwindow *window, double xPos, double yPos) {
    if (!s_EnableCursor) {
        if (s_FirstMouse) {
            s_LastX = xPos;
            s_LastY = yPos;
            s_FirstMouse = false;
        }

        float xOffset = xPos - s_LastX;
        s_LastX = xPos;
        float yOffset = s_LastY - yPos;
        s_LastY = yPos;

        s_Camera.ProcessMouseMovement(xOffset, yOffset);
    }
}

static void MouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    if (!s_EnableCursor)
        s_Camera.ProcessMouseScroll(static_cast<float>(yOffset));
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
        if (s_IsFoolScreen) {
            s_Width = 800;
            s_Height = 600;
            glfwSetWindowMonitor(window, NULL, 0, 0, s_Width, s_Height, GLFW_DONT_CARE);
        } else {
            s_Width = 1366;
            s_Height = 768;
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, s_Width, s_Height, GLFW_DONT_CARE);
        }
        s_IsFoolScreen = !s_IsFoolScreen;
    }

    if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS) {
        if (s_EnableCursor) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            s_FirstMouse = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        s_EnableCursor = !s_EnableCursor;
    }
}

int main() {
    if (glfwInit() == GLFW_FALSE) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(s_Width, s_Height, "Hello World", NULL, NULL);

    if (window == NULL) {
        std::cerr << "Failed to create a window and its opengl context!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!s_EnableCursor)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSetCursorPosCallback(window, MouseMoveCallback);
    glfwSetScrollCallback(window, MouseScrollCallback);
    glfwSetKeyCallback(window, KeyCallback);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    GLCall(glEnable(GL_DEPTH_TEST));

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

    glm::vec3 cubePositions[] = {
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

    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    glm::vec3 pointLightColors[] = {
        glm::vec3(0.2f, 0.3f, 0.8f),
        glm::vec3(0.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 0.0f)
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

{ // destructors should be called before glfwTerminate()

    VertexArray va;
    VertexBuffer vb(cubeVertices, 36 * 8 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    va.Unbind();

    VertexArray lightSourceVAO;
    lightSourceVAO.AddBuffer(vb, layout);
    lightSourceVAO.Unbind();

    glm::vec3 lightPosition(1.2f, 1.0f, 2.0f);

    Texture diffuseMap("../resources/textures/container_diffuse_map.png");
    Texture specularMap("../resources/textures/container_specular_map.png");
    Shader shader("../resources/shaders/MultipleLights.glsl");
    Shader lightSourceShader("../resources/shaders/LightSource.glsl");

    Renderer renderer;

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        s_ElapsedTime = currentFrame - s_LastFrame;
        s_LastFrame = currentFrame;

        glfwPollEvents();
        ProcessInput(window);

        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("Control panel");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            for (int i = 0; i < 4; ++i) {
                std::string idx = std::to_string(i + 1);
                if (ImGui::CollapsingHeader(("Point light " + idx).c_str())) {
                    ImGui::SliderFloat3(("Position " + idx).c_str(), &pointLightPositions[i].x, -10.0f, 10.0f);
                    ImGui::ColorEdit3(("Color " + idx).c_str(), &pointLightColors[i].r);
                }
            }

            ImGui::End();
        }

        va.Bind();
        shader.Bind();
        const glm::vec3 &cameraPosition = s_Camera.GetPosition();
        const glm::vec3 &cameraDirection = s_Camera.GetFront();

        // Directional light
        shader.SetUniform3f("u_DirLight.direction", -lightPosition.x, -lightPosition.y, -lightPosition.z);
        shader.SetUniform3f("u_DirLight.ambient", 0.1f, 0.1f, 0.1f);
        shader.SetUniform3f("u_DirLight.diffuse", 1.0f, 1.0f, 1.0f);
        shader.SetUniform3f("u_DirLight.specular", 1.0f, 1.0f, 1.0f);

        // Point light 1
        for (int i = 0; i < 4; ++i) {
            std::string idx = std::to_string(i);
            shader.SetUniform3f(("u_PointLights[" + idx + "].position").c_str(), pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);
            shader.SetUniform3f(("u_PointLights[" + idx + "].ambient").c_str(), 0.1f, 0.1f, 0.1f);
            shader.SetUniform3f(("u_PointLights[" + idx + "].diffuse").c_str(), pointLightColors[i].r, pointLightColors[i].g, pointLightColors[i].b);
            shader.SetUniform3f(("u_PointLights[" + idx + "].specular").c_str(), pointLightColors[i].r, pointLightColors[i].g, pointLightColors[i].b);
            shader.SetUniform1f(("u_PointLights[" + idx + "].constant").c_str(), 1.0f);
            shader.SetUniform1f(("u_PointLights[" + idx + "].linear").c_str(), 0.09f);
            shader.SetUniform1f(("u_PointLights[" + idx + "].quadratic").c_str(), 0.032f);
        }

        shader.SetUniform3f("u_SpotLight.position", cameraPosition.x, cameraPosition.y, cameraPosition.z);
        shader.SetUniform3f("u_SpotLight.direction", cameraDirection.x, cameraDirection.y, cameraDirection.z);
        shader.SetUniform1f("u_SpotLight.innerCutOff", glm::cos(glm::radians(5.0f)));
        shader.SetUniform1f("u_SpotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        shader.SetUniform3f("u_SpotLight.ambient", 0.1f, 0.1f, 0.1f);
        shader.SetUniform3f("u_SpotLight.diffuse", 0.0f, 0.0f, 1.0f);
        shader.SetUniform3f("u_SpotLight.specular", 0.0f, 0.0f, 1.0f);
        shader.SetUniform1f("u_SpotLight.constant", 1.0f);
        shader.SetUniform1f("u_SpotLight.linear", 0.09f);
        shader.SetUniform1f("u_SpotLight.quadratic", 0.032f);

        diffuseMap.Bind(0);
        specularMap.Bind(1);
        shader.SetUniform1i("u_Material.diffuse", 0);
        shader.SetUniform1i("u_Material.specular", 1);
        shader.SetUniform1f("u_Material.shininess", 32.0f);

        shader.SetUniform3f("u_ViewerPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);

        glm::mat4 view = s_Camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(s_Camera.GetFoV()), s_Width / s_Height, 0.1f, 100.0f);
        shader.SetUniformMat4f("u_View", view);
        shader.SetUniformMat4f("u_Projection", projection);

        for(unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i * (i % 2 ? glfwGetTime() : 1);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetUniformMat4f("u_Model", model);

            GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
        }

        lightSourceVAO.Bind();
        lightSourceShader.Bind();
        lightSourceShader.SetUniformMat4f("u_View", view);
        lightSourceShader.SetUniformMat4f("u_Projection", projection);

        for (int i = 0; i < 4; ++i) {
            glm::mat4 model(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lightSourceShader.SetUniformMat4f("u_Model", model);
            lightSourceShader.SetUniform3f("u_Color", pointLightColors[i].r, pointLightColors[i].g, pointLightColors[i].b);
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

} // destructors should be called before glfwTerminate()

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}