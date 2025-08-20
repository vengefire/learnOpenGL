#pragma once
#include "../../framework/events/TEventBase.h"

namespace openGL::event
{
  class MouseInputEventData : public framework::events::EventDataBase
  {
  public:
    MouseInputEventData(double xpos, double ypos, double xoffset, double yoffset, int button, int action)
      : y_offset(yoffset), x_offset(xoffset), x_pos(xpos), y_pos(ypos), button(button), action(action)
    {
    }

    double y_offset; // Y offset of the mouse movement (for scroll event)
    double x_offset; // X offset of the mouse movement (for scroll event)
    double x_pos; // X position of the mouse
    double y_pos; // Y position of the mouse
    int button; // Mouse button pressed or released
    int action; // Action performed (press/release)
  };

  class MouseInputEvent :
    public framework::events::TEventBase<MouseInputEventData>
  {
  public:
    MouseInputEvent() : TEventBase<MouseInputEventData>("Mouse Input Event") {}
    ~MouseInputEvent() override = default;
  };
}
