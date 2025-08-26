#pragma once

#include <algorithm>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "../core/OpenGLCore.h"
#include "../entity/EntityBase.h"
#include "../core/events/ProcessInputEvent.h"
#include "../core/events/FrameRenderEvent.h"
#include "../core/events/MouseInputEvent.h"

namespace openGL::camera
{
  class CameraBase : public entity::EntityBase
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
        m_camera_speed.AddEventBehavior<core::events::FrameRenderEventData>(renderEvent, [this](const core::events::FrameRenderEventData& frameRenderEventData)
        {
          return handleRenderEventForCameraSpeedProperty(std::forward<decltype(frameRenderEventData)>(frameRenderEventData));
        });

        auto inputEvent = m_pCore->get_process_input_event();
        Position->AddEventBehavior<core::events::ProcessInputEventData>(inputEvent, [this](const core::events::ProcessInputEventData& processInputEventData)
        {
          return handleInputEventForPositionProperty(std::forward<decltype(processInputEventData)>(processInputEventData));
        });

        auto mouseEvent = m_pCore->get_mouse_input_event();
        m_camera_zoom.AddEventBehavior<core::events::MouseInputEventData>(mouseEvent, [this](const core::events::MouseInputEventData& mouseInputEventData)
        {
          return handleInputEventForCameraZoom(std::forward<decltype(mouseInputEventData)>(mouseInputEventData));
        });

        Orientation->AddEventBehavior<core::events::MouseInputEventData>(mouseEvent, [this](const core::events::MouseInputEventData& mouseInputEventData)
        {
          return handleInputEventForOrientationProperty(std::forward<decltype(mouseInputEventData)>(mouseInputEventData));
          });

        m_viewport_size.AddEventBehavior<core::events::ViewPortChangeEventData>(m_pCore->get_event_by_type(typeid(core::events::ViewPortChangeEvent)), [this](const core::events::ViewPortChangeEventData& viewPortChangeEventData)
        {
          return handleFrameBufferSetEventForViewportSize(std::forward<decltype(viewPortChangeEventData)>(viewPortChangeEventData));
          });
      }
    }

    //---------------------------------------------------------------
    // Property Event Handlers
    typedef framework::property::behavior::tPropertyBehaviorData<framework::property::TPropertyBase<float>> PropertyBehaviorFloatData;
    PropertyBehaviorFloatData handleRenderEventForCameraSpeedProperty(const core::events::FrameRenderEventData& eventData)
    {
      float cameraSpeed = eventData.delta_time * 2.5f; // Adjust camera speed based on delta time
      return { cameraSpeed, framework::property::behavior::ePropertyBehaviorTypeSet };
    }

    // Handle zooming in and out
    PropertyBehaviorFloatData handleInputEventForCameraZoom(const core::events::MouseInputEventData& eventData)
    {
      return { eventData.y_offset, framework::property::behavior::ePropertyBehaviorTypeRemove };
    }

    typedef framework::property::behavior::tPropertyBehaviorData<framework::property::TPropertyBase<glm::vec2>> PropertyBehaviorVec2Data;
    PropertyBehaviorVec2Data handleFrameBufferSetEventForViewportSize(const core::events::ViewPortChangeEventData& data)
    {
      return { glm::vec2{ data.width, data.height }, framework::property::behavior::ePropertyBehaviorTypeSet };
    }

    typedef framework::property::behavior::tPropertyBehaviorData<framework::property::TPropertyBase<glm::vec3>> PropertyBehaviorVec3Data;
    PropertyBehaviorVec3Data handleInputEventForPositionProperty(const core::events::ProcessInputEventData& eventData)
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

    PropertyBehaviorVec3Data handleInputEventForOrientationProperty(const core::events::MouseInputEventData& eventData)
    {
      static auto firstMouse = true; // Flag to check if it's the first mouse movement

      if (firstMouse)
      {
        last_x_ = eventData.x_pos; // Initialize lastX_ with the current mouse position
        last_y_ = eventData.y_pos; // Initialize lastY_ with the current mouse position
        firstMouse = false; // Set the flag to false after the first mouse movement
      }

      if ((eventData.x_pos == 0.0 && eventData.y_pos == 0.0) || (!enable_pitch && !enable_yaw))
      {
        return {glm::vec3{0.0f}, framework::property::behavior::ePropertyBehaviorTypeIgnore }; // Ignore event with zero position
      }

      glm::vec3 newOrientation = Orientation->PropertyValue;

      handle_yaw_offset(eventData);
      handle_pitch_offset(eventData);
      update_camera_vectors();

      return { glm::vec3{0.0f}, framework::property::behavior::ePropertyBehaviorTypeIgnore };
    }
    //---------------------------------------------------------------

    static std::shared_ptr<CameraBase> Create(const std::shared_ptr<core::OpenGLCore>& pCore, glm::vec3 position, glm::vec3 camera_target)
    {
      auto newCamera = std::make_shared<CameraBase>(pCore, position, camera_target);
      newCamera->initialize_entity_properties();
      return newCamera;
    }

    ~CameraBase() override = default;

    virtual glm::mat4 getViewMatrix()
    {
      return glm::lookAt(Position->PropertyValue, Position->PropertyValue + front_, up_);
    }

    float near_plane_ = 0.1f;
    float far_plane_ = 100.0f;
    float get_aspect_ratio() { return m_viewport_size.PropertyValue.x / m_viewport_size.PropertyValue.y; }

    virtual glm::mat4 get_projection_matrix()
    {
      return getProjectionMatrix(get_aspect_ratio(), near_plane_, far_plane_);
    }

    virtual glm::mat4 getProjectionMatrix(float aspect_ratio, float near_plane, float far_plane)
    {
      return glm::perspective(glm::radians(m_camera_zoom.PropertyValue), aspect_ratio, near_plane, far_plane);
      //return glm::ortho(-5.0f,5.0f,-5 / get_aspect_ratio(),5 / get_aspect_ratio(), -10.0f, 10.0f);
    }

    void handle_yaw_offset(const core::events::MouseInputEventData& eventData)
    {
      if (enable_yaw)
      {
        auto xOffSet = eventData.x_pos - last_x_;
        last_x_ = eventData.x_pos;
        xOffSet *= yaw_sensitivity_;
        yaw_ += xOffSet;
      }
    }

    void handle_pitch_offset(const core::events::MouseInputEventData& eventData)
    {
      if (enable_pitch)
      {
        auto yOffSet = last_y_ - eventData.y_pos; // Invert y-axis for mouse movement
        last_y_ = eventData.y_pos;
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
    EntityPropertyFloat m_camera_zoom = EntityPropertyFloat(45.0f, 1.0f, 70.0f);
    EntityProperty2Vec m_viewport_size = EntityProperty2Vec(glm::vec2(800.0f, 600.0f), glm::vec2(320.0f, 240.0f), glm::vec2(3840.0f, 2160.0f));
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
