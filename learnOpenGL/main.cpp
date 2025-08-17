#include "config.h"
#include "openGL/models/ModelBase.h"
#include "openGL/shaders/ShaderProgram.h"

void ProcessInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}

int main()
{
  try
  {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
      throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
      glViewport(0, 0, width, height);
    });

    openGL::models::ModelBase triangleModel1;
    triangleModel1.set_vertices({
      -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left  - Red
      0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom Right - Green
      -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f   // Top Center   - Blue
      });

    openGL::models::ModelBase triangleModel2;
    triangleModel2.set_vertices({
      0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left  - Red
      1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom Right - Green
      0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f   // Top Center   - Blue
      });

    openGL::models::ModelBase rectModel1;
    rectModel1.set_vertices({
      0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,   // top right
      0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
      -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f   // top left 
      }
    );
    rectModel1.set_indices({
      0, 1, 3,
      1, 2, 3
      });

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    openGL::shaders::ShaderProgram defaultShader;
    defaultShader.load_shader_from_file("./res/shaders/shader.vs", GL_VERTEX_SHADER);
    defaultShader.load_shader_from_file("./res/shaders/shader.fs", GL_FRAGMENT_SHADER);
    defaultShader.linkProgram();
    defaultShader.use();
    defaultShader.set_float("offsetX", 0.25f);

    while (!glfwWindowShouldClose(window))
    {
      ProcessInput(window);
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Models
      triangleModel1.render();
      triangleModel2.render();
      rectModel1.render();

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    glfwTerminate();
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << '\n';
    glfwTerminate();
    return -1;
  }
  catch (...)
  {
    std::cerr << "Unknown exception occurred." << '\n';
    glfwTerminate();
    return -1;
  }
}
