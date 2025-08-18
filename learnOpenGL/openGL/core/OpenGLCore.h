#pragma once

#include "../../config.h"
#include "../models/ModelBase.h"
#include "../../framework/events/EventPublisher.h"
#include "../../framework/events/TEventSubscriberBase.h"
#include "../Events/ProcessInputEvent.h"
#include "../Events/FrameRenderEvent.h"
#include "../Events/MouseInputEvent.h"

namespace openGL::core
{
  class OpenGLCore
    : public framework::events::EventPublisher,
      public framework::events::TEventSubscriberBase<events::ProcessInputEventData>
  {
  public:
    events::ProcessInputEvent* get_process_input_event() const
    {
      return static_cast<events::ProcessInputEvent*>(get_event_by_type(typeid(events::ProcessInputEvent)));
    }
    void handle_event(std::shared_ptr<events::ProcessInputEventData> pEventData) override;

    events::FrameRenderEvent* get_render_event()
    {
      return static_cast<events::FrameRenderEvent*>(get_event_by_type(typeid(events::FrameRenderEvent)));
    }

    events::MouseInputEvent* get_mouse_input_event()
    {
      return static_cast<events::MouseInputEvent*>(get_event_by_type(typeid(events::MouseInputEvent)));
    }

    OpenGLCore(int majorVersion, int minorVersion);
    virtual ~OpenGLCore();
    void createWindow(int width, int height, const char* title);
    void run() const;
    void toggleWireFrameMode();
    void toggleCursorCaptureMode();
    void enable_depth_testing() const;
    void create_glfw_window(int width, int height, const char* title);
    static void set_current_context(GLFWwindow* pWindow);
    static void initialize_glad();
    void set_viewport_and_framebuffer_callback(int width, int height) const;
    std::shared_ptr<GLFWwindow> getWindow();

    void addModel(std::shared_ptr<models::ModelBase> model);

  protected:
    void init(int majorVersion, int minorVersion);
    static void processInput(GLFWwindow* window);

  private:
    bool cursorCaptureMode = false;
    bool wireFrameMode = false;
    std::shared_ptr<GLFWwindow> pWindow_;
    std::vector<std::shared_ptr<models::ModelBase>> models_;
  };
}
