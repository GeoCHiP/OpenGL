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

static Camera s_Camera(glm::vec3(0.0f, 0.0f, 5.0f));

static float s_Width = 800.0f;
static float s_Height = 600.0f;
static bool s_IsFoolScreen = false;

static bool s_FirstMouse = true;
static float s_LastX = s_Width / 2;
static float s_LastY = s_Height / 2;

static float s_ElapsedTime = 0.0f;
static float s_LastFrame = 0.0f;

static void PrintMatrix(const glm::mat4 &m) {
    std::cout << "Matrix" << std::endl;
    std::streamsize prev_width = std::cout.width(12);
    std::left(std::cout);
    for (int i = 0; i < m.length(); ++i) {
        for (int j = 0; j < m[0].length(); ++j) {
            std::cout.width(15);
            std::cout << m[j][i];
        }
        std::cout << std::endl;
    }

    std::cout.width(prev_width);
}

template <int L>
static void PrintVec(const glm::vec<L, float, glm::packed_highp> &v) {
    for (int i = 0; i < L - 1; ++i)
        std::cout << v[i] << ", ";
    std::cout << v[L-1] << std::endl;
}

static void ProcessInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) {
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

static void MouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    s_Camera.ProcessMouseScroll(static_cast<float>(yOffset));
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSetCursorPosCallback(window, MouseMoveCallback);
    glfwSetScrollCallback(window, MouseScrollCallback);

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
    Shader shader("../resources/shaders/Basic.glsl");
    Shader lightSourceShader("../resources/shaders/LightSource.glsl");

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        s_ElapsedTime = currentFrame - s_LastFrame;
        s_LastFrame = currentFrame;

        glfwPollEvents();
        ProcessInput(window);

        renderer.Clear();

        va.Bind();
        shader.Bind();
        shader.SetUniform3f("u_Light.position", lightPosition.x, lightPosition.y, lightPosition.z);
        shader.SetUniform3f("u_Light.ambient", 0.1f, 0.1f, 0.1f);
        shader.SetUniform3f("u_Light.diffuse", 1.0f, 1.0f, 1.0f);
        shader.SetUniform3f("u_Light.specular", 1.0f, 1.0f, 1.0f);

        diffuseMap.Bind(0);
        specularMap.Bind(1);
        shader.SetUniform1i("u_Material.diffuse", 0);
        shader.SetUniform1i("u_Material.specular", 1);
        shader.SetUniform1f("u_Material.shininess", 0.6f);

        const glm::vec3 &viewerPosition = s_Camera.GetPosition();
        shader.SetUniform3f("u_ViewerPosition", viewerPosition.x, viewerPosition.y, viewerPosition.z);

        glm::mat4 model(1.0f);
        glm::mat4 view = s_Camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(s_Camera.GetFoV()), s_Width / s_Height, 0.1f, 100.0f);
        shader.SetUniformMat4f("u_Model", model);
        shader.SetUniformMat4f("u_View", view);
        shader.SetUniformMat4f("u_Projection", projection);

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

        lightSourceVAO.Bind();
        lightSourceShader.Bind();
        model = glm::translate(model, lightPosition);
        model = glm::scale(model, glm::vec3(0.2f));
        lightSourceShader.SetUniformMat4f("u_Model", model);
        lightSourceShader.SetUniformMat4f("u_View", view);
        lightSourceShader.SetUniformMat4f("u_Projection", projection);

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

        glfwSwapBuffers(window);
    }

} // destructors should be called before glfwTerminate()
    glfwTerminate();
    return 0;
}