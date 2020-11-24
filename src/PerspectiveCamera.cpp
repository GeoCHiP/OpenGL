#include "PerspectiveCamera.h"

#include "glm/gtc/matrix_transform.hpp"

// Defualt camera values
static const float DEF_YAW = -90.0f;
static const float DEF_PITCH = 0.0f;
static const float DEF_SPEED = 2.5f;
static const float DEF_SENSITIVITY = 0.1f;
static const float DEF_FOV = 45.0f;

PerspectiveCamera::PerspectiveCamera(glm::vec3 position, glm::vec3 center, glm::vec3 worldUp, float fov,
        float aspect)
        : Camera(position), m_WorldUp(worldUp), m_Yaw(DEF_YAW), m_Pitch(DEF_PITCH),
        m_Speed(DEF_SPEED), m_MouseSensitivity(DEF_SENSITIVITY), m_FoV(DEF_FOV), m_AspectRatio(aspect) {
    UpdateCameraVectors();
    m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    m_ProjectionMatrix = glm::perspective(m_FoV, m_AspectRatio, 0.1f, 100.0f);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

PerspectiveCamera::~PerspectiveCamera() {}

void PerspectiveCamera::ProcessKeyboard(CameraMovement direction, float elapsedTime) {
    float velocity = m_Speed * elapsedTime;

    switch (direction) {
        case CameraMovement::Forward:
            m_Position += m_Front * velocity;
            break;
        case CameraMovement::Backward:
            m_Position -= m_Front * velocity;
            break;
        case CameraMovement::Leftward:
            m_Position -= m_Right * velocity;
            break;
        case CameraMovement::Rightward:
            m_Position += m_Right * velocity;
            break;
        case CameraMovement::Upward:
            m_Position += m_Up * velocity;
            break;
        case CameraMovement::Downward:
            m_Position -= m_Up * velocity;
            break;
    }

    RecalculateViewMatrix();
}

void PerspectiveCamera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    m_Yaw += xOffset * m_MouseSensitivity;
    m_Pitch += yOffset * m_MouseSensitivity;

    if (constrainPitch) {
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0f;
        else if (m_Pitch < -89.0f)
            m_Pitch = -89.0f;
    }

    UpdateCameraVectors();
}

void PerspectiveCamera::ProcessMouseScroll(float yOffset) {
    m_FoV -= yOffset;

    if (m_FoV < 1.0f)
        m_FoV = 1.0f;
    else if (m_FoV > 45.0f)
        m_FoV = 45.0f;
    
    RecalculateProjectionMatrix();
}

void PerspectiveCamera::UpdateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    newFront.y = sin(glm::radians(m_Pitch));
    newFront.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(newFront);

    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));

    RecalculateViewMatrix();
}

void PerspectiveCamera::RecalculateViewMatrix() {
    m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void PerspectiveCamera::RecalculateProjectionMatrix() {
    m_ProjectionMatrix = glm::perspective(glm::radians(m_FoV), m_AspectRatio, 0.1f, 100.0f);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}