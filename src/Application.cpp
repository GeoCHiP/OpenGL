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

#include "tests/TestMultipleLights.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


static Camera s_Camera(glm::vec3(0.0f, 0.0f, 5.0f));

static float s_Width = 800.0f;
static float s_Height = 600.0f;
static bool s_IsFoolScreen = false;
static bool s_EnableCursor = true;

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
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

{ // destructors should be called before glfwTerminate()

    Renderer renderer;

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    test::TestMultipleLights test;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        s_ElapsedTime = currentFrame - s_LastFrame;
        s_LastFrame = currentFrame;

        glfwPollEvents();
        ProcessInput(window);

        renderer.Clear();

        test.OnUpdate(0.0f);
        test.OnRender(s_Camera, s_Width / s_Height);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        test.OnImGuiRender();

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