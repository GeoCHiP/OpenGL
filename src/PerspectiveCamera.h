#pragma once

#include "Camera.h"

class PerspectiveCamera : public Camera {
public:
    // center -- position where the camera is looking at
    PerspectiveCamera(glm::vec3 position, glm::vec3 center, glm::vec3 worldUp, float fov, float aspect);
    ~PerspectiveCamera() override;

    void ProcessKeyboard(CameraMovement direction, float elapsedTime);
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yOffset);

    void SetAspectRatio(float newAspectRatio) { m_AspectRatio = newAspectRatio; RecalculateProjectionMatrix(); }

    const glm::vec3 &GetFront() const { return m_Front; }
    float GetFoV() const { return m_FoV; }
    float GetAspectRatio() const { return m_AspectRatio; }

    const glm::vec3 &GetPosition() const override { return m_Position; }
    const glm::mat4 &GetViewMatrix() const override { return m_ViewMatrix; }
    const glm::mat4 &GetProjectionMatrix() const override { return m_ProjectionMatrix; }
    const glm::mat4 &GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }

private:
    void UpdateCameraVectors();
    void RecalculateViewMatrix();
    void RecalculateProjectionMatrix();

private:
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;
    glm::vec3 m_WorldUp;

    float m_Yaw;
    float m_Pitch;
    float m_Speed;
    float m_MouseSensitivity;
    float m_FoV;
    float m_AspectRatio;
};