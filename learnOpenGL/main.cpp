#include "config.h"
#include "openGL/models/ModelBase.h"
#include "openGL/shaders/ShaderProgram.h"
#include "openGL/core/OpenGLCore.h"

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
    openGL::core::OpenGLCore core(3, 3);
    core.createWindow(800, 600, "Learn OpenGL");

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

    openGL::shaders::ShaderProgram defaultShader;
    defaultShader.load_shader_from_file("./res/shaders/shader.vs", GL_VERTEX_SHADER);
    defaultShader.load_shader_from_file("./res/shaders/shader.fs", GL_FRAGMENT_SHADER);
    defaultShader.linkProgram();
    defaultShader.use();
    defaultShader.set_float("offsetX", 0.25f);

    core.run();
    /*while (!glfwWindowShouldClose(window))
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
    }*/

    //glfwTerminate();
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << '\n';
    //glfwTerminate();
    return -1;
  }
  catch (...)
  {
    std::cerr << "Unknown exception occurred." << '\n';
    //glfwTerminate();
    return -1;
  }
}
