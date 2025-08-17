#include "OpenGLCore.h"

namespace openGL::core
{
  OpenGLCore::OpenGLCore(int majorVersion, int minorVersion)
  {
    init(majorVersion, minorVersion);
  }

  OpenGLCore::~OpenGLCore()
  {
    glfwTerminate();
  }

  void OpenGLCore::init(int majorVersion, int minorVersion)
  {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      throw std::runtime_error("Failed to initialize GLAD");
    }
  }
}
