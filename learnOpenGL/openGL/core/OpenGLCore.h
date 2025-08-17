#pragma once

#include "../../config.h"

namespace openGL::core
{
  class OpenGLCore
  {
    public:
    OpenGLCore(int majorVersion, int minorVersion);
    virtual ~OpenGLCore();
    void init(int majorVersion, int minorVersion);
    void processInput(GLFWwindow* window);
    void run();
  protected:
  private:
  };
}