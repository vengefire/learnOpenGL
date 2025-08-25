#pragma once
#include <GLFW/glfw3.h>

#include "../../../framework/events/TEventBase.h"

namespace openGL::core::events
{
  class ViewPortChangeEventData : public framework::events::EventDataBase
  {
  public:
    ViewPortChangeEventData(GLFWwindow* p_glfw_window, int width, int height)
      : pGLFWWindow(p_glfw_window),
      width(width),
      height(height)
    {
    }

    // Add any additional data members or methods if needed
    GLFWwindow* pGLFWWindow = nullptr;
    int width = 800;
    int height = 600;
  };

  class ViewPortChangeEvent : public framework::events::TEventBase<ViewPortChangeEventData>
  {
  public:
    ViewPortChangeEvent() : TEventBase<ViewPortChangeEventData>("View Port Changed Event")
    {
    }
    ~ViewPortChangeEvent() override = default;
  };
}
