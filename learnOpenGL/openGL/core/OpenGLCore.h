#pragma once

#include "../../config.h"
#include "../model/ModelBase.h"
#include "../../framework/events/EventPublisher.h"
#include "../../framework/events/TEventSubscriberBase.h"
#include "../event/ProcessInputEvent.h"
#include "../event/FrameRenderEvent.h"
#include "../event/MouseInputEvent.h"

namespace openGL::core
{
  class OpenGLCore
    : public framework::events::EventPublisher,
      public framework::events::TEventSubscriberBase<event::ProcessInputEventData>
  {
  public:
    event::ProcessInputEvent* get_process_input_event() const
    {
      return static_cast<event::ProcessInputEvent*>(get_event_by_type(typeid(event::ProcessInputEvent)));
    }
    void handle_event(std::shared_ptr<event::ProcessInputEventData> pEventData) override;

    event::FrameRenderEvent* get_render_event()
    {
      return static_cast<event::FrameRenderEvent*>(get_event_by_type(typeid(event::FrameRenderEvent)));
    }

    event::MouseInputEvent* get_mouse_input_event()
    {
      return static_cast<event::MouseInputEvent*>(get_event_by_type(typeid(event::MouseInputEvent)));
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

    void addModel(std::shared_ptr<model::ModelBase> model);

  protected:
    void init(int majorVersion, int minorVersion);
    static void processInput(GLFWwindow* window);

  private:
    bool cursorCaptureMode = false;
    bool wireFrameMode = false;
    std::shared_ptr<GLFWwindow> pWindow_;
    std::vector<std::shared_ptr<model::ModelBase>> models_;
  };
}
