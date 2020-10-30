#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch, float speed, float mouseSensitivity, float FoV)
              : m_Position(position), m_WorldUp(worldUp), m_Yaw(yaw), m_Pitch(pitch),
                m_Speed(speed), m_MouseSensitivity(mouseSensitivity), m_FoV(FoV) {
    UpdateCameraVectors();
}

Camera::~Camera() {}

void Camera::ProcessKeyboard(CameraMovement direction, float elapsedTime) {
    float velocity = m_Speed * elapsedTime;

    switch (direction) {
        case CameraMovement::Forward:
            m_Position += m_Front * velocity;
            break;
        case CameraMovement::Backward:
            m_Position -= m_Front * velocity;
            break;
        case CameraMovement::Left:
            m_Position -= m_Right * velocity;
            break;
        case CameraMovement::Right:
            m_Position += m_Right * velocity;
            break;
    }
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
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

void Camera::ProcessMouseScroll(float yOffset) {
    m_FoV -= yOffset;

    if (m_FoV < 1.0f)
        m_FoV = 1.0f;
    else if (m_FoV > 45.0f)
        m_FoV = 45.0f;
}

void Camera::UpdateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    newFront.y = sin(glm::radians(m_Pitch));
    newFront.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(newFront);
    
    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}