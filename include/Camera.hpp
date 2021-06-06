#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Core/Base.hpp"
#include "Graphic/CameraBase.hpp"
#include "Graphic/GLContext.hpp"
#include "Transform.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

class Camera : public te::CameraBase, public Transform {
public:
  Camera(int x, int y, int width, int height);

  virtual glm::mat4 getView() const override;

  virtual glm::mat4 getProjection() const override;
};

#endif  // CAMERA_HPP