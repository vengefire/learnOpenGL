#include "config.h"
#include "openGL/models/ModelBase.h"
#include "openGL/shaders/ShaderProgram.h"
#include "openGL/core/OpenGLCore.h"
#include "openGL/camera/CameraBase.h"
#include "stb_image_impl.h"
#include "openGL/primitives/GridPrimitive.h"
#include "openGL/primitives/PlanePrimitive.h"

int main()
{
  try
  {
    openGL::core::OpenGLCore core(3, 3);
    core.createWindow(800, 600, "Learn OpenGL");

    auto camera = std::make_shared<openGL::camera::CameraBase>();
    auto inputEvent = core.get_process_input_event();
    auto renderEvent = core.get_render_event();
    auto mouseInputEvent = core.get_mouse_input_event();
    renderEvent->subscribe(static_cast<framework::events::TEventSubscriberBase<openGL::events::FrameRenderEventData>*>(camera.get()));
    inputEvent->subscribe(static_cast<framework::events::TEventSubscriberBase<openGL::events::ProcessInputEventData>*>(camera.get()));
    mouseInputEvent->subscribe(static_cast<framework::events::TEventSubscriberBase<openGL::events::MouseInputEventData>*>(camera.get()));
    /*
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
    // core.addModel(triModel1);

    auto triModel2 = std::make_shared<openGL::models::ModelBase>();
    triModel2->set_vertices({
      { 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f }, // Bottom Left  - Red
      { 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f }, // Bottom Right - Green
      { 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f }   // Top Center   - Blue
      });
    triModel2->set_shader_program(defaultColouredVertexShader);
    // core.addModel(triModel2);
    */

    // Texture shader program for textured vertices
    auto texturedVertexShader = std::make_shared<openGL::shaders::ShaderProgram>("Textured Shader Program");
    texturedVertexShader->load_shader_from_file("./res/shaders/texturedshader.vs", GL_VERTEX_SHADER);
    texturedVertexShader->load_shader_from_file("./res/shaders/texturedshader.fs", GL_FRAGMENT_SHADER);
    texturedVertexShader->linkProgram();

    /*auto rectModel1 = std::make_shared<openGL::models::ModelBase>();
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
    rectModel1->set_texture_from_file("./res/textures/awesomeface.jpg");
    core.get_process_input_event()->subscribe(rectModel1.get());
    rectModel1->RotationX = -55.0f; // Rotate the rectangle by 45 degrees around the X-axis
    core.addModel(rectModel1);*/
    auto cubeModel = std::make_shared<openGL::models::ModelBase>(texturedVertexShader);
    cubeModel->set_vertices({
    {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f},
     {0.5f, -0.5f, -0.5f,  1.0f, 0.0f},
     {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
     {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
    {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
    {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f},

    {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
     {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
     {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
     {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
    {-0.5f,  0.5f,  0.5f,  0.0f, 1.0f},
    {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},

    {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
    {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
    {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
    {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
    {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
    {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

     {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
     {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
     {0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
     {0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
     {0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
     {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

    {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
     {0.5f, -0.5f, -0.5f,  1.0f, 1.0f},
     {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
     {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
    {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
    {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},

    {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
     {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
     {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
     {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
    {-0.5f,  0.5f,  0.5f,  0.0f, 0.0f},
    {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f} });

    cubeModel->set_texture_from_file("./res/textures/container.jpg");
    cubeModel->set_texture_from_file("./res/textures/awesomeface.jpg");
    inputEvent->subscribe(cubeModel.get());
    // cubeModel->RotationX = -55.0f; // Rotate the rectangle by 45 degrees around the X-axis
    // cubeModel->TranslationY = 1.0f; // Move the cube up by 1 unit
    cubeModel->set_camera(camera);

    auto planePrimitive = openGL::primitives::PlanePrimitive::generate_plane(5.0f, 5.0f, 10, 10);
    auto planeModel = std::make_shared<openGL::models::ModelBase>(texturedVertexShader);
    planeModel->set_vertices(planePrimitive.get_vertices());
    planeModel->set_indices(planePrimitive.get_indices());
    planeModel->set_camera(camera);
    planeModel->RotationX = -90.0f;
    planeModel->RotationZ = 45.0f; // Rotate the plane by 45 degrees around the Z-axis
    planeModel->TranslationY = -2.0f; // Move the plane down by 2 units

    auto gridPrimitive = openGL::primitives::GridPrimitive::generate_grid_(5.0f, 5.0f, 5.0f, 2, 1);
    auto gridModel = std::make_shared<openGL::models::ModelBase>(texturedVertexShader);
    gridModel->set_vertices(gridPrimitive.get_vertices());
    gridModel->DrawLines = true; // Set the grid model to draw lines
    gridModel->RotationX = -90.0f;
    // gridModel->RotationZ = 45.0f;
    // gridModel->TranslationY = -1.0f; // Move the grid down by 1 unit
    gridModel->set_camera(camera);

    core.addModel(planeModel);
    core.addModel(cubeModel);
    core.addModel(gridModel);

    core.enable_depth_testing();

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
