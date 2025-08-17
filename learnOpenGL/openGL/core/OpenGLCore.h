#pragma once

#include "../../config.h"
#include "../models/ModelBase.h"

namespace openGL::core
{
  class OpenGLCore
  {
  public:
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

    void addModel(const models::ModelBase& model);

  protected:
    static void init(int majorVersion, int minorVersion);
    static void processInput(GLFWwindow* window);

  private:
    bool wireFrameMode = false;
    std::shared_ptr<GLFWwindow> pWindow_;
    std::vector<models::ModelBase> models_;
  };
}
