#pragma once

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../../framework/events/TEventSubscriberBase.h"
#include "../Events/ProcessInputEvent.h"

namespace openGL::camera
{
  class CameraBase : public framework::events::TEventSubscriberBase<events::ProcessInputEventData>
  {
  public:
    CameraBase() : CameraBase(glm::vec3(0.0f,0.0f,3.0f), glm::vec3(0.0,0.0,4.0))
    {
    }

    CameraBase(glm::vec3 position, glm::vec3 camera_target) : position_(position)
    {
      // Initialize the front vector to point in the negative z direction
      front_ = glm::normalize(position_ - camera_target);
      // Calculate the right vector as the cross product of the front vector and the default world up vector
      right_ = glm::normalize(glm::cross(front_, glm::vec3(0.0f, 1.0f, 0.0f)));
      // Calculate the up vector as the cross product of the right vector and the front vector
      up_ = glm::normalize(glm::cross(right_, front_));
    }

    virtual ~CameraBase()
    {
    }

    virtual glm::mat4 getViewMatrix()
    {
      return glm::lookAt(position_, position_ + front_, up_);
    }

    void handle_event(events::ProcessInputEventData* pEventData)
    {
      // Handle input events here, e.g., update camera position or orientation based on input
      // This is a placeholder implementation; actual input handling logic should be added.
      if (!pEventData)
      {
        return; // Handle null pointer case
      }
      // Example: Update camera position based on input data
      // Rotation
      if (glfwGetKey(pEventData->window, GLFW_KEY_A) == GLFW_PRESS)
      {
        rotationY_ += 0.1f;
      }
      else if (glfwGetKey(pEventData->window, GLFW_KEY_D) == GLFW_PRESS)
      {
        rotationY_ -= 0.1f;
      }

      if (glfwGetKey(pEventData->window, GLFW_KEY_W) == GLFW_PRESS)
      {
        rotationX_ += 0.1f;
      }
      else if (glfwGetKey(pEventData->window, GLFW_KEY_S) == GLFW_PRESS)
      {
        rotationX_ -= 0.1f;
      }

      if (glfwGetKey(pEventData->window, GLFW_KEY_Q) == GLFW_PRESS)
      {
        rotationZ_ += 0.1f;
      }
      else if (glfwGetKey(pEventData->window, GLFW_KEY_E) == GLFW_PRESS)
      {
        rotationZ_ -= 0.1f;
      }

      // Translation / Movement
      if (glfwGetKey(pEventData->window, GLFW_KEY_UP) == GLFW_PRESS)
      {
        position_ += front_ * camera_speed;
      }
      else if (glfwGetKey(pEventData->window, GLFW_KEY_DOWN) == GLFW_PRESS)
      {
        position_ -= front_ * camera_speed;
      }

      if (glfwGetKey(pEventData->window, GLFW_KEY_LEFT) == GLFW_PRESS)
      {
        position_ -= glm::normalize(glm::cross(front_, up_)) * camera_speed;
      }
      else if (glfwGetKey(pEventData->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      {
        position_ += glm::normalize(glm::cross(front_, up_)) * camera_speed;
      }

      if (glfwGetKey(pEventData->window, GLFW_KEY_R) == GLFW_PRESS)
      {
        position_ -= glm::normalize(glm::cross(front_, right_)) * camera_speed;
      }
      else if (glfwGetKey(pEventData->window, GLFW_KEY_F) == GLFW_PRESS)
      {
        position_ += glm::normalize(glm::cross(front_, right_)) * camera_speed;
      }
    }

  protected:
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 right_;
    glm::vec3 up_;
    float camera_speed = 0.05f; // Adjust the speed of the camera movement
    float rotationY_;
    float rotationX_;
    float rotationZ_;
  };
}
