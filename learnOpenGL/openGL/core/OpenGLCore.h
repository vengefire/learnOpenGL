#pragma once

#include "../../config.h"
#include "../models/ModelBase.h"
#include "../../framework/events/EventPublisher.h"
#include "../../framework/events/TEventSubscriberBase.h"
#include "../Events/ProcessInputEvent.h"

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
    void handle_event(events::ProcessInputEventData* pEventData) override;
    OpenGLCore(int majorVersion, int minorVersion);
    virtual ~OpenGLCore();
    void createWindow(int width, int height, const char* title);
    void run() const;
    void toggleWireFrameMode();
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
    bool wireFrameMode = false;
    std::shared_ptr<GLFWwindow> pWindow_;
    std::vector<std::shared_ptr<models::ModelBase>> models_;
  };
}
