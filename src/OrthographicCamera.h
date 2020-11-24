#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"

class OrthographicCamera : public Camera {
public:
    OrthographicCamera(float left, float right, float bottom, float top);
    ~OrthographicCamera();

    void ProcessKeyboard(CameraMovement direction, float elapsedTime);
    void ProcessMouseScroll(float yOffset);

    void SetPosition(const glm::vec3 &position) { m_Position = position; RecalculateViewMatrix(); }
    void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
    void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }

    float GetRotation() const { return m_Rotation; }
    float GetAspectRatio() const { return m_AspectRatio; }

    const glm::vec3 &GetPosition() const override { return m_Position; }
    const glm::mat4 &GetViewMatrix() const override { return m_ViewMatrix; }
    const glm::mat4 &GetProjectionMatrix() const override { return m_ProjectionMatrix; }
    const glm::mat4 &GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }

private:
    void RecalculateViewMatrix();

private:
    float m_Rotation;
    float m_Speed;
    float m_AspectRatio;
};