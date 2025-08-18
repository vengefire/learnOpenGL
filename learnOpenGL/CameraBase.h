#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace openGL::camera
{
  class CameraBase
  {
  public:
    CameraBase()
    {
      // Default Camera position
      position_ = glm::vec3(0.0f, 0.0f, 3.0f);

      // Initialize the front vector to point in the negative z direction
      front_ = glm::normalize(position_ - glm::vec3(0.0f, 0.0f, 0.0f));

      // Calculate the right vector as the cross product of the front vector and the world up vector
      right_ = glm::normalize(glm::cross(front_, glm::vec3(0.0f, 1.0f, 0.0f)));

      // Calculate the up vector as the cross product of the right vector and the front vector
      up_ = glm::normalize(glm::cross(right_, front_));
    }
  protected:
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 right_;
    glm::vec3 up_;
  };
}
