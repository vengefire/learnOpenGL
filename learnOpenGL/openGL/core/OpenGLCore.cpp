#include "OpenGLCore.h"

#include "../model/ModelBase.h"

namespace openGL::core
{
  void OpenGLCore::handle_event(std::shared_ptr<events::ViewPortChangeEventData> pEventData)
  {
    glViewport(0, 0, pEventData->width, pEventData->height);
  }

  void OpenGLCore::handle_event(std::shared_ptr<core::events::ProcessInputEventData>  pEventData)
  {
    if (glfwGetKey(pEventData->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(pEventData->window, true);
    }
  }

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

  void OpenGLCore::set_viewport_and_framebuffer_callback(int width, int height)
  {
    glViewport(0, 0, width, height);
    auto viewPortChangedEvent = add_event(std::make_unique<core::events::ViewPortChangeEvent>());
    glfwSetFramebufferSizeCallback(
      pWindow_.get(),
      [](GLFWwindow* window, int width, int height)
      {
        auto pThisCore = static_cast<OpenGLCore*>(glfwGetWindowUserPointer(window));
        if (pThisCore)
        {
          if (auto viewPortChangedEvent = pThisCore->get_event_by_type(typeid(core::events::ViewPortChangeEvent)))
          {
            viewPortChangedEvent->emit_event(std::make_shared<core::events::ViewPortChangeEventData>(window, width, height));
          }
        }
      }
    );
    glfwSetWindowUserPointer(pWindow_.get(), this);
    viewPortChangedEvent->register_subscriber(static_cast<TEventSubscriberBase<core::events::ViewPortChangeEventData>*>(this));
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

    add_event(std::make_unique<core::events::ProcessInputEvent>(pWindow_.get(), 0.0f));
    add_event(std::make_unique<core::events::FrameRenderEvent>());
    toggleCursorCaptureMode();
    static auto mouseInputEvent = add_event(std::make_unique<core::events::MouseInputEvent>());
    glfwSetCursorPosCallback(pWindow_.get(), [](GLFWwindow* window, double xpos, double ypos)
      {
        if (!mouseInputEvent)
        {
          return;
        }
        mouseInputEvent->emit_event(std::make_shared<core::events::MouseInputEventData>(xpos, ypos, 0, 0, 0, 0));
      });

    glfwSetMouseButtonCallback(pWindow_.get(), [](GLFWwindow* window, int button, int action, int mods)
      {
        if (!mouseInputEvent)
        {
          return;
        }
        mouseInputEvent->emit_event(std::make_shared<core::events::MouseInputEventData>(0, 0, 0, 0, button, action));
      });

    glfwSetScrollCallback(pWindow_.get(), [](GLFWwindow* window, double xoffset, double yoffset)
      {
        if (!mouseInputEvent)
        {
          return;
        }
        mouseInputEvent->emit_event(std::make_shared<core::events::MouseInputEventData>(0, 0, xoffset, yoffset, 0, 0));
      });

    TEventSubscriberBase<core::events::ProcessInputEventData>* me = this;
    register_subscriber(me, typeid(core::events::ProcessInputEvent));
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
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(pWindow_.get()))
    {
      double currentFrame = glfwGetTime();
      double deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      emit_event(typeid(core::events::ProcessInputEvent));
      emit_event(typeid(core::events::FrameRenderEvent), std::make_shared<core::events::FrameRenderEventData>(deltaTime, lastFrame));

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      // Render your models here
      for (const auto model : models_)
      {
        model->renderModel();
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

  void OpenGLCore::toggleCursorCaptureMode()
  {
    cursorCaptureMode = !cursorCaptureMode;
    if (cursorCaptureMode)
    {
      glfwSetInputMode(pWindow_.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      std::cout << "Cursor capture mode enabled" << std::endl;
    }
    else
    {
      glfwSetInputMode(pWindow_.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      std::cout << "Cursor capture mode disabled" << std::endl;
    }
  }

  void OpenGLCore::enable_depth_testing() const
  {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    std::cout << "Depth testing enabled" << std::endl;
  }

  std::shared_ptr<GLFWwindow> OpenGLCore::getWindow()
  {
    return pWindow_;
  }

  void OpenGLCore::addModel(std::shared_ptr<model::ModelBase> model)
  {
    models_.push_back(model);
  }
}
