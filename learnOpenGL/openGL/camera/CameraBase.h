#pragma once

#include <algorithm>
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
    CameraBase() : CameraBase(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0, 0.0, 4.0))
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

    ~CameraBase() override
    {
    }

    virtual glm::mat4 getViewMatrix()
    {
      return glm::lookAt(position_, position_ + front_, up_);
    }

    float near_plane_ = 0.1f;
    float far_plane_ = 100.0f;

    float width_ = 800;
    float _height = 600;
    float get_aspect_ratio() const { return width_ / _height; }

    virtual glm::mat4 get_projection_matrix()
    {
      return getProjectionMatrix(get_aspect_ratio(), near_plane_, far_plane_);
    }

    virtual glm::mat4 getProjectionMatrix(float aspect_ratio, float near_plane, float far_plane)
    {
      return glm::perspective(glm::radians(camera_zoom_), aspect_ratio, near_plane, far_plane);
    }

    void handle_event(std::shared_ptr<events::FrameRenderEventData> pEventData) override
    {
      if (!pEventData) return; // Handle null pointer case
      camera_speed_ = pEventData->delta_time * 2.5f; // Adjust camera speed based on delta time
    }

    void handle_event(std::shared_ptr<events::MouseInputEventData> pEventData) override
    {
      static auto firstMouse = true; // Flag to check if it's the first mouse movement
      if (!pEventData) return; // Handle null pointer case

      if (firstMouse)
      {
        last_x_ = pEventData->x_pos; // Initialize lastX_ with the current mouse position
        last_y_ = pEventData->y_pos; // Initialize lastY_ with the current mouse position
        firstMouse = false; // Set the flag to false after the first mouse movement
      }
      // Handle zooming in and out
      camera_zoom_ -= pEventData->y_offset; // Adjust zoom based on mouse scroll
      camera_zoom_ = std::max(camera_zoom_, 1.0f); // Prevent zooming in too much
      camera_zoom_ = std::min(camera_zoom_, 45.0f); // Prevent zooming out too much

      if (pEventData->x_pos == 0 && pEventData->y_pos == 0)
      {
        return; // Ignore events with zero position
      }

      auto xOffSet = pEventData->x_pos - last_x_;
      auto yOffSet = last_y_ - pEventData->y_pos; // Invert y-axis for mouse movement
      last_x_ = pEventData->x_pos;
      last_y_ = pEventData->y_pos;
      xOffSet *= yaw_sensitivity_;
      yOffSet *= pitch_sensitivity_;
      yaw_ += xOffSet;
      pitch_ += yOffSet;

      // Clamp the pitch value to prevent flipping
      pitch_ = std::min(pitch_, 89.0f);
      pitch_ = std::max(pitch_, -89.0f);

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

    void handle_event(std::shared_ptr<events::ProcessInputEventData> pEventData) override
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
        position_ += front_ * camera_speed_;
      }
      else if (glfwGetKey(pEventData->window, GLFW_KEY_DOWN) == GLFW_PRESS)
      {
        position_ -= front_ * camera_speed_;
      }

      if (glfwGetKey(pEventData->window, GLFW_KEY_LEFT) == GLFW_PRESS)
      {
        position_ -= glm::normalize(glm::cross(front_, up_)) * camera_speed_;
      }
      else if (glfwGetKey(pEventData->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      {
        position_ += glm::normalize(glm::cross(front_, up_)) * camera_speed_;
      }

      if (glfwGetKey(pEventData->window, GLFW_KEY_R) == GLFW_PRESS)
      {
        position_ -= glm::normalize(glm::cross(front_, right_)) * camera_speed_;
      }
      else if (glfwGetKey(pEventData->window, GLFW_KEY_F) == GLFW_PRESS)
      {
        position_ += glm::normalize(glm::cross(front_, right_)) * camera_speed_;
      }
    }

  protected:
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 right_;
    glm::vec3 up_;

    float camera_zoom_ = 45.0f;
    float camera_speed_ = 0.05f; // Adjust the speed of the camera movement

    float yaw_sensitivity_ = 0.1f;
    float pitch_sensitivity_ = 0.1f;
    float roll_sensitivity_ = 0.1f;
    float last_x_ = 400, last_y_ = 300;
    float yaw_ = -90.0f; // Yaw
    float pitch_ = 0.0f; // Pitch
    float roll_ = 0.0f; // Roll
  };
}
