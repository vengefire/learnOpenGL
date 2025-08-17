#include "config.h"
#include "openGL/models/ModelBase.h"
#include "openGL/shaders/ShaderProgram.h"
#include "openGL/core/OpenGLCore.h"
#include "stb_image_impl.h"

int main()
{
  try
  {
    openGL::core::OpenGLCore core(3, 3);
    core.createWindow(800, 600, "Learn OpenGL");

    // Default shader program for coloured vertices
    auto defaultColouredVertexShader = std::make_shared<openGL::shaders::ShaderProgram>("Default Coloured Shader");
    defaultColouredVertexShader->load_shader_from_file("./res/shaders/shader.vs", GL_VERTEX_SHADER);
    defaultColouredVertexShader->load_shader_from_file("./res/shaders/shader.fs", GL_FRAGMENT_SHADER);
    defaultColouredVertexShader->linkProgram();

    auto triModel1 = std::make_shared<openGL::models::ModelBase>();
    triModel1->set_vertices({
      { -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f }, // Bottom Left  - Red
      { 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f },  // Bottom Right - Green
      { -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f }   // Top Center   - Blue
      });
    triModel1->set_shader_program(defaultColouredVertexShader);
    core.addModel(triModel1);

    auto triModel2 = std::make_shared<openGL::models::ModelBase>();
    triModel2->set_vertices({
      { 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f }, // Bottom Left  - Red
      { 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f }, // Bottom Right - Green
      { 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f }   // Top Center   - Blue
      });
    triModel2->set_shader_program(defaultColouredVertexShader);
    core.addModel(triModel2);

    // Texture shader program for textured coloured vertices
    auto texturedColouredVertexShader = std::make_shared<openGL::shaders::ShaderProgram>("Textured Coloured Shader");
    texturedColouredVertexShader->load_shader_from_file("./res/shaders/texturedshader.vs", GL_VERTEX_SHADER);
    texturedColouredVertexShader->load_shader_from_file("./res/shaders/texturedshader.fs", GL_FRAGMENT_SHADER);
    texturedColouredVertexShader->linkProgram();

    texturedColouredVertexShader->use();
    texturedColouredVertexShader->set_int("texture1", 0); // Set texture unit 0 for texture1
    texturedColouredVertexShader->set_int("texture2", 1); // Set texture unit 1 for texture2

    auto rectModel1 = std::make_shared<openGL::models::ModelBase>();
    rectModel1->set_vertices({
         {0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f}, // top right
         {0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f, 1.0f, 0.0f}, // bottom right
        {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, // bottom left
        {-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f}  // top left 
      }
    );

    rectModel1->set_indices({
      0, 1, 3,
      1, 2, 3
    });

    rectModel1->set_shader_program(texturedColouredVertexShader);
    rectModel1->set_texture_from_file("./res/textures/container.jpg");
    rectModel1->set_texture_from_file("./res/textures/awesomeface.png");
    core.addModel(rectModel1);

    core.run();
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << '\n';
    return -1;
  }
  catch (...)
  {
    std::cerr << "Unknown exception occurred." << '\n';
    return -1;
  }
}
