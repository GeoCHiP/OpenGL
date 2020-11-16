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

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

const float WIDTH = 800;
const float HEIGHT = 600;

bool firstMouse = true;
float lastX = WIDTH / 2;
float lastY = HEIGHT / 2;

float elapsedTime = 0.0f;
float lastFrame = 0.0f;

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
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::Forward, elapsedTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::Backward, elapsedTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::Left, elapsedTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::Right, elapsedTime);
}

static void FramebufferSizeCallback(GLFWwindow *window, int width, int height) {
    GLCall(glViewport(0, 0, width, height));
}

static void MouseMoveCallback(GLFWwindow *window, double xPos, double yPos) {
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float xOffset = xPos - lastX;
    lastX = xPos;
    float yOffset = lastY - yPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}

void MouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    camera.ProcessMouseScroll(static_cast<float>(yOffset));
}

int main() {
    if (glfwInit() == GLFW_FALSE) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);

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
        // Position
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

{ // destructors should be called before glfwTerminate()

    VertexArray va;
    VertexBuffer vb(cubeVertices, 36 * 3 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    va.AddBuffer(vb, layout);
    va.Unbind();

    VertexArray lightSourceVAO;
    lightSourceVAO.AddBuffer(vb, layout);
    lightSourceVAO.Unbind();

    Shader shader("../resources/shaders/Basic.glsl");
    shader.Bind();
    shader.SetUniform4f("u_LightColor", 1.0f, 1.0f, 1.0f, 1.0f);
    shader.SetUniform4f("u_ObjectColor", 1.0f, 0.5f, 0.31f, 1.0f);
    glm::mat4 model(1.0f);
    shader.SetUniformMat4f("u_Model", model);
    shader.Unbind();

    Shader lightSourceShader("../resources/shaders/LightSource.glsl");
    lightSourceShader.Bind();
    lightSourceShader.SetUniform4f("u_LightColor", 1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPosition(1.2f, 1.0f, 2.0f);
    model = glm::translate(model, lightPosition);
    model = glm::scale(model, glm::vec3(0.2f));
    lightSourceShader.SetUniformMat4f("u_Model", model);
    lightSourceShader.Unbind();

    Renderer renderer;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        elapsedTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        ProcessInput(window);

        glm::mat4 view = camera.GetViewMatrix();
        shader.Bind();
        shader.SetUniformMat4f("u_View", view);
        lightSourceShader.Bind();
        lightSourceShader.SetUniformMat4f("u_View", view);

        glm::mat4 projection = glm::perspective(glm::radians(camera.GetFoV()), WIDTH / HEIGHT, 0.1f, 100.0f);
        shader.Bind();
        shader.SetUniformMat4f("u_Projection", projection);
        lightSourceShader.Bind();
        lightSourceShader.SetUniformMat4f("u_Projection", projection);

        renderer.Clear();

        va.Bind();
        shader.Bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

        lightSourceVAO.Bind();
        lightSourceShader.Bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
        lightSourceShader.Bind();

        glfwSwapBuffers(window);
    }

} // destructors should be called before glfwTerminate()
    glfwTerminate();
    return 0;
}