#pragma once
#include "../../framework/events/TEventBase.h"

namespace openGL::events
{
  class MouseInputEventData : public framework::events::EventDataBase
  {
  public:
    MouseInputEventData(double xpos, double ypos, int button, int action)
      : x_pos(xpos), y_pos(ypos), button(button), action(action)
    {
    }

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
