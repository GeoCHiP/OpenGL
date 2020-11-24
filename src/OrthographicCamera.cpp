#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
    m_ViewMatrix(glm::mat4(1.0f)),
    m_Speed(1.0f) {
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