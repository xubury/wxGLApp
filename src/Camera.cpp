#include "Camera.hpp"

Camera::Camera(int x, int y, int width, int height) : te::CameraBase(x, y, width, height)
{
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(getPosition(), getPosition() - getFront(), getUp());
}

glm::mat4 Camera::getProjection() const
{
    return glm::perspective(glm::radians(45.f), getAspect(), getNearZ(), getFarZ());
}