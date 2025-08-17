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
    std::cout << "OpenGL Terminated" << std::endl;
  }

  void OpenGLCore::init(int majorVersion, int minorVersion)
  {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    std::cout << "OpenGL Init - Version: " << majorVersion << "." << minorVersion << std::endl;
  }

  void OpenGLCore::set_current_context(GLFWwindow* pWindow)
  {
    glfwMakeContextCurrent(pWindow);
  }

  void OpenGLCore::initialize_glad()
  {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      throw std::runtime_error("Failed to initialize GLAD");
    }
  }

  void OpenGLCore::set_viewport_and_framebuffer_callback(int width, int height) const
  {
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(pWindow_.get(), [](GLFWwindow* window, int width, int height)
    {
      glViewport(0, 0, width, height);
    });
  }

  void OpenGLCore::create_glfw_window(int width, int height, const char* title)
  {
    pWindow_ = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, title, nullptr, nullptr),
                                           [](GLFWwindow* window)
                                           {
                                             glfwDestroyWindow(window);
                                           });

    if (!pWindow_)
    {
      throw std::runtime_error("Failed to create GLFW window");
    }
  }

  void OpenGLCore::createWindow(int width, int height, const char* title)
  {
    create_glfw_window(width, height, title);
    set_current_context(pWindow_.get());
    initialize_glad();
    set_viewport_and_framebuffer_callback(width, height);
  }

  void OpenGLCore::processInput(GLFWwindow* window)
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, true);
    }
  }

  void OpenGLCore::run() const
  {
    while (!glfwWindowShouldClose(pWindow_.get()))
    {
      processInput(pWindow_.get());
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      // Render your models here
      for (const auto model : models_)
      {
        model->render();
      }
      glfwSwapBuffers(pWindow_.get());
      glfwPollEvents();
    }
  }

  void OpenGLCore::toggleWireFrameMode()
  {
    wireFrameMode = !wireFrameMode;
    if (wireFrameMode)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  }

  std::shared_ptr<GLFWwindow> OpenGLCore::getWindow()
  {
    return pWindow_;
  }

  void OpenGLCore::addModel(std::shared_ptr<models::ModelBase> model)
  {
    models_.push_back(model);
  }
}
