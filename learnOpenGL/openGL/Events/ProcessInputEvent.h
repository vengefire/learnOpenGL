#pragma once

#include "../../config.h"
#include "../../framework/events/TEventBase.h"
#include "../../framework/events/EventDataBase.h"

namespace openGL::events
{
  class ProcessInputEventData : public framework::events::EventDataBase
  {
  public:
    ProcessInputEventData(GLFWwindow* window, float deltaTime)
      : window(window), delta_time(deltaTime) {
    }
    GLFWwindow* window;
    float delta_time;
  };

  class ProcessInputEvent : public framework::events::TEventBase<ProcessInputEventData>
  {
    public:
    ProcessInputEvent(GLFWwindow* window, float deltaTime)
      : TEventBase<ProcessInputEventData>("ProcessInputEvent",std::make_unique<ProcessInputEventData>(ProcessInputEventData{ window, deltaTime })) {}
    ~ProcessInputEvent() = default;
    void handle_event()
    {
      // Process input logic here
      // Example: Check for key presses, mouse movements, etc.
      auto data = this->get_event_data();
      if (glfwGetKey(data->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      {
        glfwSetWindowShouldClose(data->window, true);
      }
      // Add more input handling as needed
    }
  };

}
