#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"

class OrthographicCamera {
public:
    OrthographicCamera(float left, float right, float bottom, float top);
    ~OrthographicCamera();

    void ProcessKeyboard(CameraMovement direction, float elapsedTime);
    void ProcessMouseScroll(float yOffset);

    void SetPosition(const glm::vec3 &position) { m_Position = position; RecalculateViewMatrix(); }
    void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

    float GetRotation() const { return m_Rotation; }

    const glm::vec3 &GetPosition() const { return m_Position; }
    const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
    const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }
    const glm::mat4 &GetVeiwProjectionMatrix() const { return m_ViewProjectionMatrix; }

private:
    void RecalculateViewMatrix();

private:
    glm::vec3 m_Position;
    float m_Rotation;
    float m_Speed;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewProjectionMatrix;
};