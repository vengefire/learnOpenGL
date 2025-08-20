#pragma once
#include "../../framework/events/TEventBase.h"

namespace openGL::event
{
  class FrameRenderEventData : public framework::events::EventDataBase
  {
  public:
    FrameRenderEventData(float delta_time, float last_frame)
      : delta_time(delta_time), last_frame(last_frame)
    {
    }
    // Add any additional data members or methods if needed
    float delta_time = 0.0f; // Time since last frame
    float last_frame = 0.0f; // Time of the last frame
  };

  class FrameRenderEvent : public framework::events::TEventBase<FrameRenderEventData>
  {
  public:
    FrameRenderEvent() : TEventBase<FrameRenderEventData>("Frame Render Event")
    {
    }
    ~FrameRenderEvent() override = default;
  };
}
