#pragma once

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../../framework/events/TEventSubscriberBase.h"
#include "../Events/ProcessInputEvent.h"
#include "../Events/FrameRenderEvent.h"
#include "../Events/MouseInputEvent.h"

namespace openGL::camera
{
  class CameraBase :
    public framework::events::TEventSubscriberBase<events::ProcessInputEventData>,
    public framework::events::TEventSubscriberBase<events::FrameRenderEventData>,
    public framework::events::TEventSubscriberBase<events::MouseInputEventData>
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

    void handle_event(std::shared_ptr<events::FrameRenderEventData> pEventData)
    {
      if (!pEventData) return; // Handle null pointer case
      camera_speed = pEventData->delta_time * 2.5f; // Adjust camera speed based on delta time
    }

    void handle_event(std::shared_ptr<events::MouseInputEventData> pEventData) override
    {
      static auto firstMouse = true; // Flag to check if it's the first mouse movement
      if (!pEventData) return; // Handle null pointer case

      if (firstMouse)
      {
        lastX_ = pEventData->x_pos; // Initialize lastX_ with the current mouse position
        lastY_ = pEventData->y_pos; // Initialize lastY_ with the current mouse position
        firstMouse = false; // Set the flag to false after the first mouse movement
      }

      auto xOffSet = pEventData->x_pos - lastX_;
      auto yOffSet = lastY_ - pEventData->y_pos; // Invert y-axis for mouse movement
      lastX_ = pEventData->x_pos;
      lastY_ = pEventData->y_pos;
      xOffSet *= yaw_sensitivity;
      yOffSet *= pitch_sensitivity;
      yaw_ += xOffSet;
      pitch_ += yOffSet;
      // Clamp the pitch value to prevent flipping
      if (pitch_ > 89.0f) pitch_ = 89.0f;
      if (pitch_ < -89.0f) pitch_ = -89.0f;
      // Update the front vector based on yaw and pitch
      glm::vec3 front;
      front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
      front.y = sin(glm::radians(pitch_));
      front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
      front_ = glm::normalize(front);
      // Update the right and up vectors
      right_ = glm::normalize(glm::cross(front_, glm::vec3(0.0f, 1.0f, 0.0f)));
      up_ = glm::normalize(glm::cross(right_, front_));
    }

    void handle_event(std::shared_ptr<events::ProcessInputEventData> pEventData)
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
        yaw_ += 0.1f;
      }
      else if (glfwGetKey(pEventData->window, GLFW_KEY_D) == GLFW_PRESS)
      {
        yaw_ -= 0.1f;
      }

      if (glfwGetKey(pEventData->window, GLFW_KEY_W) == GLFW_PRESS)
      {
        pitch_ += 0.1f;
      }
      else if (glfwGetKey(pEventData->window, GLFW_KEY_S) == GLFW_PRESS)
      {
        pitch_ -= 0.1f;
      }

      if (glfwGetKey(pEventData->window, GLFW_KEY_Q) == GLFW_PRESS)
      {
        roll_ += 0.1f;
      }
      else if (glfwGetKey(pEventData->window, GLFW_KEY_E) == GLFW_PRESS)
      {
        roll_ -= 0.1f;
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

    float yaw_sensitivity = 0.1f; 
    float pitch_sensitivity = 0.1f;
    float roll_sensitivity = 0.1f;
    float lastX_ = 400, lastY_ = 300;
    float yaw_ = -90.0f; // Yaw
    float pitch_ = 0.0f; // Pitch
    float roll_ = 0.0f; // Roll
  };
}
