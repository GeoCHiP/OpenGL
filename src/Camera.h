#pragma once

#include "glm/glm.hpp"

enum class CameraMovement {
    Forward = 0, Backward, Leftward, Rightward, Downward, Upward
};

class Camera {
public:
    Camera(const glm::vec3 &position) : m_Position(position) {}
    virtual ~Camera() {}

    virtual const glm::vec3 &GetPosition() const = 0;
    virtual const glm::mat4 &GetViewMatrix() const = 0;
    virtual const glm::mat4 &GetProjectionMatrix() const = 0;
    virtual const glm::mat4 &GetViewProjectionMatrix() const = 0;

protected:
    glm::vec3 m_Position;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewProjectionMatrix;
};