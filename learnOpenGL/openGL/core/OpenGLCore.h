#pragma once

#include "../../config.h"

namespace openGL::core
{
  class OpenGLCore
  {
  public:
    OpenGLCore(int majorVersion, int minorVersion);
    virtual ~OpenGLCore();
    void createWindow(int width, int height, const char* title);
    static void processInput(GLFWwindow* window);
    void run() const;
    void toggleWireFrameMode();

    std::shared_ptr<GLFWwindow> getWindow()
    {
      return pWindow_;
    }

  protected:
    static void init(int majorVersion, int minorVersion);
  private:
    bool wireFrameMode = false;
    std::shared_ptr<GLFWwindow> pWindow_;
  };
}