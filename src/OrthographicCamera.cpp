#include "OrthographicCamera.h"

// Default camera values
static const float DEF_SPEED = 2.5f;

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : Camera(glm::vec3(0.0f, 0.0f, 0.0f)), m_Speed(DEF_SPEED) {
        m_ViewMatrix = glm::mat4(1.0f);
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

OrthographicCamera::~OrthographicCamera() {}

void OrthographicCamera::RecalculateViewMatrix() {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::ProcessKeyboard(CameraMovement direction, float elapsedTime) {
    float velocity = m_Speed * elapsedTime;

    switch (direction) {
        case CameraMovement::Leftward:
            m_Position.x -= velocity;
            break;
        case CameraMovement::Rightward:
            m_Position.x += velocity;
            break;
        case CameraMovement::Upward:
            m_Position.y += velocity;
            break;
        case CameraMovement::Downward:
            m_Position.y -= velocity;
            break;
    }

    RecalculateViewMatrix();
}