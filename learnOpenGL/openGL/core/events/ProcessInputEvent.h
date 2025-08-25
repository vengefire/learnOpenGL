#pragma once

#include "../../../config.h"
#include "../../../framework/events/TEventBase.h"
#include "../../../framework/events/EventDataBase.h"

namespace openGL::core::events
{
  class ProcessInputEventData : public framework::events::EventDataBase
  {
  public:
    ProcessInputEventData(GLFWwindow* window, float deltaTime)
      : window(window), delta_time(deltaTime)
    {
    }

    GLFWwindow* window;
    float delta_time;
  };

  class ProcessInputEvent : public framework::events::TEventBase<ProcessInputEventData>
  {
  public:
    ProcessInputEvent(GLFWwindow* window, float deltaTime)
      : TEventBase<ProcessInputEventData>("ProcessInputEvent",
                                          std::make_unique<ProcessInputEventData>(ProcessInputEventData{
                                            window, deltaTime
                                          }))
    {
    }

    ~ProcessInputEvent() override = default;
  };
}
