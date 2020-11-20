#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Defualt camera values
static const float DEF_YAW = -90.0f;
static const float DEF_PITCH = 0.0f;
static const float DEF_SPEED = 2.5f;
static const float DEF_SENSITIVITY = 0.1f;
static const float DEF_FOV = 45.0f;

enum class CameraMovement {
    Forward = 0, Backward, Leftward, Rightward, Downward, Upward
};

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = DEF_YAW, float pitch = DEF_PITCH,
           float speed = DEF_SPEED, float mouseSensitivity = DEF_SENSITIVITY, float FoV = DEF_FOV);
    ~Camera();

    void ProcessKeyboard(CameraMovement direction, float elapsedTime);
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yOffset);

    inline glm::mat4 GetViewMatrix() const { return glm::lookAt(m_Position, m_Position + m_Front, m_Up); }
    inline float GetFoV() const { return m_FoV; }
    inline const glm::vec3 &GetPosition() const { return m_Position; }

private:
    void UpdateCameraVectors();

private:
    glm::vec3 m_Position;
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;

    float m_Yaw;
    float m_Pitch;
    float m_Speed;
    float m_MouseSensitivity;
    float m_FoV;
};