#pragma once

#include "../../config.h"
#include "../../framework/events/EventPublisher.h"
#include "../../framework/events/TEventSubscriberBase.h"
#include "events/FrameRenderEvent.h"
#include "events/MouseInputEvent.h"
#include "events/ProcessInputEvent.h"
#include "events/ViewPortChangeEvent.h"


namespace openGL::model
{
  class ModelBase;
}

namespace openGL::core
{
  class OpenGLCore
    : public framework::events::EventPublisher,
      public framework::events::TEventSubscriberBase<core::events::ProcessInputEventData>,
      public framework::events::TEventSubscriberBase<core::events::ViewPortChangeEventData>
  {
  public:
    void handle_event(std::shared_ptr<events::ViewPortChangeEventData> pEventData) override;

    static void glfwFramebufferSizeCallbackWrapper(GLFWwindow* window, int width, int height);
  public:
    std::shared_ptr<core::events::ProcessInputEvent> get_process_input_event() const
    {
      return std::dynamic_pointer_cast<core::events::ProcessInputEvent>(get_event_by_type(typeid(core::events::ProcessInputEvent)));
    }
    void handle_event(std::shared_ptr<core::events::ProcessInputEventData> pEventData) override;

    std::shared_ptr<core::events::FrameRenderEvent> get_render_event()
    {
      return std::dynamic_pointer_cast<core::events::FrameRenderEvent>(get_event_by_type(typeid(core::events::FrameRenderEvent)));
    }

    std::shared_ptr<core::events::MouseInputEvent> get_mouse_input_event()
    {
      return std::dynamic_pointer_cast<core::events::MouseInputEvent>(get_event_by_type(typeid(core::events::MouseInputEvent)));
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
    void set_viewport_and_framebuffer_callback(int width, int height);
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
