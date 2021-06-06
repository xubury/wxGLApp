#include "Light.hpp"

glm::mat4 Light::getLightSpaceMatrix() const {
    const glm::vec3 &up = getUp();
    const glm::vec3 &front = getFront();
    const glm::vec3 &pos = getPosition();
    glm::mat4 lightView = glm::lookAt(pos, pos + front, up);
    float near_plane = 0.1f, far_plane = 100.f;
    glm::mat4 lightProjection =
        glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    return lightProjection * lightView;
}

glm::vec3 Light::getDirection() const {
    return getFront();
}

glm::vec3 Light::getPosition() const {
    return Transform::getPosition();
}