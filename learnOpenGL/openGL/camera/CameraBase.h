#pragma once

#include <algorithm>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../core/OpenGLCore.h"
#include "../../framework/events/TEventSubscriberBase.h"
#include "../entity/EntityBase.h"
#include "../event/ProcessInputEvent.h"
#include "../event/FrameRenderEvent.h"
#include "../event/MouseInputEvent.h"

namespace openGL::camera
{
  class CameraBase :
    public framework::events::TEventSubscriberBase<event::MouseInputEventData>
    , public entity::EntityBase
  {
  public:

    CameraBase() : CameraBase(nullptr, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0, 0.0, 4.0))
    {
    }

    CameraBase(const std::shared_ptr<core::OpenGLCore>& pCore, glm::vec3 position, glm::vec3 camera_target)
      : m_pCore(pCore)
    {
      set_position(position);
      // Initialize the front vector to point in the negative z direction
      front_ = glm::normalize(Position->PropertyValue - camera_target);
      // Calculate the right vector as the cross product of the front vector and the default world up vector
      right_ = glm::normalize(glm::cross(front_, glm::vec3(0.0f, 1.0f, 0.0f)));
      // Calculate the up vector as the cross product of the right vector and the front vector
      up_ = glm::normalize(glm::cross(right_, front_));

      if (m_pCore)
      {
        auto renderEvent = m_pCore->get_render_event();
        m_camera_speed.AddEventBehavior<event::FrameRenderEventData>(renderEvent, [this](const event::FrameRenderEventData& frameRenderEventData)
        {
          return handleRenderEventForCameraSpeedProperty(std::forward<decltype(frameRenderEventData)>(frameRenderEventData));
        });

        auto inputEvent = m_pCore->get_process_input_event();
        Position->AddEventBehavior<event::ProcessInputEventData>(inputEvent, [this](const event::ProcessInputEventData& processInputEventData)
        {
          return handleInputEventForPositionProperty(std::forward<decltype(processInputEventData)>(processInputEventData));
        });

        auto mouseEvent = m_pCore->get_mouse_input_event();
        m_camera_zoom.AddEventBehavior<event::MouseInputEventData>(mouseEvent, [this](const event::MouseInputEventData& mouseInputEventData)
        {
          return handleInputEventForCameraZoom(std::forward<decltype(mouseInputEventData)>(mouseInputEventData));
        });
      }
    }

    //---------------------------------------------------------------
    // Property Event Handlers
    typedef framework::property::behavior::tPropertyBehaviorData<framework::property::TPropertyBase<float>> PropertyBehaviorFloatData;
    PropertyBehaviorFloatData handleRenderEventForCameraSpeedProperty(const event::FrameRenderEventData& eventData)
    {
      float cameraSpeed = eventData.delta_time * 2.5f; // Adjust camera speed based on delta time
      return { cameraSpeed, framework::property::behavior::ePropertyBehaviorTypeSet };
    }

    // Handle zooming in and out
    PropertyBehaviorFloatData handleInputEventForCameraZoom(const event::MouseInputEventData& eventData)
    {
      return { eventData.y_offset, framework::property::behavior::ePropertyBehaviorTypeRemove };
      //return { std::min(std::max(static_cast<float>(eventData.y_offset), 1.0f), 70.0f), framework::property::behavior::ePropertyBehaviorTypeRemove };
    }

    typedef framework::property::behavior::tPropertyBehaviorData<framework::property::TPropertyBase<glm::vec3>> PropertyBehaviorVec3Data;
    PropertyBehaviorVec3Data handleInputEventForPositionProperty(const event::ProcessInputEventData& eventData)
    {
      glm::vec3 newPosition = Position->PropertyValue;
      if (enable_camera_movement_z)
      {
        if (glfwGetKey(eventData.window, GLFW_KEY_W) == GLFW_PRESS)
        {
          newPosition += front_ * m_camera_speed.PropertyValue;
        }
        else if (glfwGetKey(eventData.window, GLFW_KEY_S) == GLFW_PRESS)
        {
          newPosition -= front_ * m_camera_speed.PropertyValue;
        }
      }

      if (enable_camera_movement_x)
      {
        if (glfwGetKey(eventData.window, GLFW_KEY_A) == GLFW_PRESS)
        {
          newPosition -= right_ * m_camera_speed.PropertyValue;
        }
        else if (glfwGetKey(eventData.window, GLFW_KEY_D) == GLFW_PRESS)
        {
          newPosition += right_ * m_camera_speed.PropertyValue;
        }
      }

      if (enable_camera_movement_y)
      {
        if (glfwGetKey(eventData.window, GLFW_KEY_R) == GLFW_PRESS)
        {
          newPosition -= glm::normalize(glm::cross(front_, right_)) * m_camera_speed.PropertyValue;
        }
        else if (glfwGetKey(eventData.window, GLFW_KEY_F) == GLFW_PRESS)
        {
          newPosition += glm::normalize(glm::cross(front_, right_)) * m_camera_speed.PropertyValue;
        }
      }
      return { EntityProperty3Vec(newPosition), framework::property::behavior::ePropertyBehaviorTypeSet };
    }
    //---------------------------------------------------------------

    static std::shared_ptr<CameraBase> Create(const std::shared_ptr<core::OpenGLCore>& pCore, glm::vec3 position, glm::vec3 camera_target)
    {
      auto newCamera = std::make_shared<CameraBase>(pCore, position, camera_target);
      newCamera->initialize_entity_properties();
      return newCamera;
    }

    ~CameraBase() override
    {
    }

    virtual glm::mat4 getViewMatrix()
    {
      return glm::lookAt(Position->PropertyValue, Position->PropertyValue + front_, up_);
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
      return glm::perspective(glm::radians(m_camera_zoom.PropertyValue), aspect_ratio, near_plane, far_plane);
    }

    void handle_yaw_offset(std::shared_ptr<event::MouseInputEventData> pEventData)
    {
      if (enable_yaw)
      {
        auto xOffSet = pEventData->x_pos - last_x_;
        last_x_ = pEventData->x_pos;
        xOffSet *= yaw_sensitivity_;
        yaw_ += xOffSet;
      }
    }

    void handle_pitch_offset(std::shared_ptr<event::MouseInputEventData> pEventData)
    {
      if (enable_pitch)
      {
        auto yOffSet = last_y_ - pEventData->y_pos; // Invert y-axis for mouse movement
        last_y_ = pEventData->y_pos;
        yOffSet *= pitch_sensitivity_;
        pitch_ += yOffSet;
        // Clamp the pitch value to prevent flipping
        pitch_ = std::min(pitch_, 89.0f);
        pitch_ = std::max(pitch_, -89.0f);
      }
    }

    void update_camera_vectors()
    {
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

    void handle_event(std::shared_ptr<event::MouseInputEventData> pEventData) override
    {
      static auto firstMouse = true; // Flag to check if it's the first mouse movement
      if (!pEventData) return; // Handle null pointer case

      if (firstMouse)
      {
        last_x_ = pEventData->x_pos; // Initialize lastX_ with the current mouse position
        last_y_ = pEventData->y_pos; // Initialize lastY_ with the current mouse position
        firstMouse = false; // Set the flag to false after the first mouse movement
      }

      // handle_camera_zoom(pEventData);

      if (pEventData->x_pos == 0.0 && pEventData->y_pos == 0.0)
      {
        return; // Ignore event with zero position
      }

      if (!enable_pitch && !enable_yaw)
      {
        return; // Ignore event if both axes are disabled
      }

      handle_yaw_offset(pEventData);
      handle_pitch_offset(pEventData);
      update_camera_vectors();
    }

    void handle_camera_movement(std::shared_ptr<event::ProcessInputEventData> pEventData)
    {
      if (enable_camera_movement_z)
      {
        if (glfwGetKey(pEventData->window, GLFW_KEY_W) == GLFW_PRESS)
        {
          *Position += front_ * m_camera_speed.PropertyValue;
        }
        else if (glfwGetKey(pEventData->window, GLFW_KEY_S) == GLFW_PRESS)
        {
          *Position -= front_ * m_camera_speed.PropertyValue;
        }
      }

      if (enable_camera_movement_x)
      {
        if (glfwGetKey(pEventData->window, GLFW_KEY_A) == GLFW_PRESS)
        {
          *Position -= right_ * m_camera_speed.PropertyValue;
        }
        else if (glfwGetKey(pEventData->window, GLFW_KEY_D) == GLFW_PRESS)
        {
          *Position += right_ * m_camera_speed.PropertyValue;
        }
      }

      if (enable_camera_movement_y)
      {
        if (glfwGetKey(pEventData->window, GLFW_KEY_R) == GLFW_PRESS)
        {
          *Position -= glm::normalize(glm::cross(front_, right_)) * m_camera_speed.PropertyValue;
        }
        else if (glfwGetKey(pEventData->window, GLFW_KEY_F) == GLFW_PRESS)
        {
          *Position += glm::normalize(glm::cross(front_, right_)) * m_camera_speed.PropertyValue;
        }
      }
    }

  protected:
    bool m_restrict_orientation_change_to_rmb_down = false;

    bool enable_yaw = true;         // Orientation about the y-axis (yaw)
    bool enable_pitch = true;       // Orientation about the x-axis (pitch)
    bool enable_roll = true;        // Orientation about the z-axis (roll)
    bool enable_camera_zoom = true; // Enable or disable camera zoom
    bool enable_camera_movement_x = true; // Enable or disable camera movement along the x-axis
    bool enable_camera_movement_y = true; // Enable or disable camera movement along the y-axis
    bool enable_camera_movement_z = true; // Enable or disable camera movement along the z-axis

    glm::vec3 front_;
    glm::vec3 right_;
    glm::vec3 up_;

    //float camera_zoom_ = 45.0f;  // Default "zoom" level for the camera, aka field of view (FOV)
    entity::property::TEntityPropertyBase<float> m_camera_speed = 0.05f;
    entity::property::TEntityPropertyBase<bool> m_mouse_capture_rmb = false;
    entity::property::TEntityPropertyBase<bool> m_mouse_capture_lmb = false;
    EntityPropertyFloat m_camera_zoom = 45.0f;
    std::shared_ptr<core::OpenGLCore> m_pCore;

    float yaw_sensitivity_ = 0.1f;
    float pitch_sensitivity_ = 0.1f;
    float roll_sensitivity_ = 0.1f;
    float last_x_ = 400, last_y_ = 300;
    float yaw_ = -90.0f; // Yaw
    float pitch_ = 0.0f; // Pitch
    float roll_ = 0.0f; // Roll
  };
}
