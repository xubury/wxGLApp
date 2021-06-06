#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Graphic/LightBase.hpp"
#include "Transform.hpp"

class Light : public te::LightBase, public Transform {
   public:
    Light() = default;

    glm::mat4 getLightSpaceMatrix() const override;

    glm::vec3 getDirection() const override;

    glm::vec3 getPosition() const override;
};

#endif  // LIGHT_HPP