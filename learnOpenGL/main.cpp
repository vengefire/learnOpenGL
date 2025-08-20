#include "config.h"
#include "openGL/model/ModelBaseDep.h"
#include "openGL/shaders/ShaderProgram.h"
#include "openGL/core/OpenGLCore.h"
#include "openGL/camera/CameraBase.h"
#include "openGL/primitives/GridPrimitive.h"
#include "openGL/primitives/PlanePrimitive.h"

#include "stb_image_impl.h"
#include "openGL/model/ModelBase.h"
#include "openGL/primitives/CirclePrimitive.h"
#include "openGL/primitives/CubePrimitive.h"
#include "openGL/primitives/TrianglePrimitive.h"
#include "openGL/primitives/UVSpherePrimitive.h"

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
    renderEvent->subscribe(static_cast<framework::events::TEventSubscriberBase<openGL::event::FrameRenderEventData>*>(camera.get()));
    inputEvent->subscribe(static_cast<framework::events::TEventSubscriberBase<openGL::event::ProcessInputEventData>*>(camera.get()));
    mouseInputEvent->subscribe(static_cast<framework::events::TEventSubscriberBase<openGL::event::MouseInputEventData>*>(camera.get()));

    // Default shader program for coloured vertices
    auto defaultColouredVertexShader = std::make_shared<openGL::shaders::ShaderProgram>("Default Coloured Shader");
    defaultColouredVertexShader->load_shader_from_file("./res/shaders/shader.vs", GL_VERTEX_SHADER);
    defaultColouredVertexShader->load_shader_from_file("./res/shaders/shader.fs", GL_FRAGMENT_SHADER);
    defaultColouredVertexShader->linkProgram();

    // Texture shader program for textured vertices
    auto texturedVertexShader = std::make_shared<openGL::shaders::ShaderProgram>("Textured Shader Program");
    texturedVertexShader->load_shader_from_file("./res/shaders/texturedshader.vs", GL_VERTEX_SHADER);
    texturedVertexShader->load_shader_from_file("./res/shaders/texturedshader.fs", GL_FRAGMENT_SHADER);
    texturedVertexShader->linkProgram();

    /*
    auto trianglePrimitive = openGL::primitives::TrianglePrimitive::generate_triangle(1.0f, 1.0f, 0.0f);
    auto triangleModel = std::make_shared<openGL::model::ModelBaseDep>(texturedVertexShader);
    triangleModel->set_vertices(trianglePrimitive.get_vertices());
    triangleModel->set_camera(camera);
    triangleModel->set_texture_from_file("./res/textures/awesomeface.jpg");
    triangleModel->TranslationX -= 2.0f;
    triangleModel->TranslationZ -= 1.0f;
    triangleModel->TranslationY += 1.0f; // Rotate the triangle by 45 degrees around the X-axis
    */
    /*auto rectModel1 = std::make_shared<openGL::models::ModelBaseDep>();
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
    /*
    auto planePrimitive = openGL::primitives::PlanePrimitive::generate_plane(5.0f, 5.0f, 1, 1);
    auto planeModel = std::make_shared<openGL::model::ModelBaseDep>(defaultColouredVertexShader);
    planeModel->set_vertices(planePrimitive.get_vertices());
    planeModel->set_indices(planePrimitive.get_indices());
    planeModel->set_camera(camera);
    planeModel->RotationX = -90.0f;
    // planeModel->RotationZ = 45.0f; // Rotate the plane by 45 degrees around the Z-axis
    planeModel->TranslationY = -2.0f; // Move the plane down by 2 units
    planeModel->UseDefaultColor = true;

    auto gridPrimitive = openGL::primitives::GridPrimitive::generate_grid_(10.0f, 10.0f, 10.0f, 11.0f, 1);
    auto gridModel = std::make_shared<openGL::model::ModelBaseDep>(defaultColouredVertexShader);
    gridModel->DefaultColor = { 0.2f, 0.2f, 0.2f, 1.0f };
    gridModel->set_vertices(gridPrimitive.get_vertices());
    gridModel->DrawLines = true; // Set the grid model to draw lines
    gridModel->RotationX = -90.0f;
    // gridModel->RotationZ = 45.0f;
    // gridModel->TranslationY = -1.0f; // Move the grid down by 1 unit
    gridModel->set_camera(camera);

    auto cubePrimitive = openGL::primitives::CubePrimitive::generate_cube_primitive(1.0f, 1.0f, 1.0f);
    auto cubePrimitiveModel = std::make_shared<openGL::model::ModelBaseDep>(texturedVertexShader);
    cubePrimitiveModel->DefaultColor = { 0.6, 0.5, 0.4, 1.0 };
    cubePrimitiveModel->UseDefaultColor = false;
    cubePrimitiveModel->set_vertices(cubePrimitive.get_vertices());
    cubePrimitiveModel->set_indices(cubePrimitive.get_indices());
    cubePrimitiveModel->set_camera(camera);
    cubePrimitiveModel->set_texture_from_file("./res/textures/container.jpg");
    cubePrimitiveModel->set_texture_from_file("./res/textures/awesomeface.jpg");

    auto circlePrimitive = openGL::primitives::CirclePrimitive::generate_circle(1.0f, 64);
    auto circleModel = std::make_shared<openGL::model::ModelBaseDep>(defaultColouredVertexShader);
    circleModel->DefaultColor = { 0.8f, 0.2f, 0.2f, 1.0f };
    circleModel->UseDefaultColor = true;
    circleModel->set_vertices(circlePrimitive.get_vertices());
    circleModel->set_indices(circlePrimitive.get_indices());
    circleModel->set_camera(camera);
    */
    /*auto uvSphereModel = std::make_shared<openGL::model::ModelBaseDep>(texturedVertexShader);
    uvSphereModel->DefaultColor = { 0.2f, 0.5f, 0.8f, 1.0f };
     uvSphereModel->UseDefaultColor = false;
    uvSphereModel->set_vertices(uvSpherePrimitive.get_vertices());
    uvSphereModel->set_indices(uvSpherePrimitive.get_indices());
    uvSphereModel->set_camera(camera);
    uvSphereModel->set_texture_from_file("./res/textures/container.jpg");
    uvSphereModel->set_texture_from_file("./res/textures/awesomeface.jpg");
    core.get_process_input_event()->subscribe(uvSphereModel.get());*/
    
    //core.addModel(triangleModel);
    //core.addModel(planeModel);
    //core.addModel(cubePrimitiveModel);
    //core.addModel(gridModel);
    //core.addModel(uvSphereModel);
    //core.addModel(circleModel);
    //core.toggleWireFrameMode();
    auto test_primitive = openGL::primitives::UVSpherePrimitive::generate_uv_sphere(64, 64, 2);
    openGL::mesh::MeshBase test_Mesh(test_primitive.get_vertices(), test_primitive.get_indices());
    auto test_model = std::make_shared<openGL::model::ModelBase>(test_Mesh, texturedVertexShader, camera);
    test_model->set_texture_from_file("./res/textures/container.jpg");
    test_model->set_texture_from_file("./res/textures/awesomeface.jpg");

    core.addModel(test_model);

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
