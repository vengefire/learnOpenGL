#include "config.h"
#include "openGL/shaders/ShaderProgram.h"
#include "openGL/core/OpenGLCore.h"
#include "openGL/camera/CameraBase.h"

#include "stb_image_impl.h"
#include "openGL/lighting/SolidColoredLight.h"
#include "openGL/model/ModelBase.h"
#include "openGL/primitives/PrimitiveFactory.h"

int main()
{
  try
  {
    openGL::core::OpenGLCore core(3, 3);
    core.createWindow(800, 600, "Learn OpenGL");

    auto inputEvent = core.get_process_input_event();
    auto renderEvent = core.get_render_event();
    auto mouseInputEvent = core.get_mouse_input_event();

    // Setup the camera
    auto camera = std::make_shared<openGL::camera::CameraBase>();

    renderEvent->subscribe(
      static_cast<framework::events::TEventSubscriberBase<openGL::event::FrameRenderEventData>*>(camera.get()));
    inputEvent->subscribe(
      static_cast<framework::events::TEventSubscriberBase<openGL::event::ProcessInputEventData>*>(camera.get()));
    mouseInputEvent->subscribe(
      static_cast<framework::events::TEventSubscriberBase<openGL::event::MouseInputEventData>*>(camera.get()));

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

    // Default shader program for coloured vertices
    // First setup the simple colored light...
    auto solidColoredLight = std::make_shared<openGL::lighting::SolidColoredLight>(glm::vec4(0.8f));
    auto lightedColouredVertexShader = std::make_shared<openGL::shaders::ShaderProgram>("Lighted Coloured Shader");
    lightedColouredVertexShader->load_shader_from_file("./res/shaders/shader.vs", GL_VERTEX_SHADER);
    lightedColouredVertexShader->load_shader_from_file("./res/shaders/light-shader.fs", GL_FRAGMENT_SHADER);
    lightedColouredVertexShader->linkProgram();
    lightedColouredVertexShader->OnRender = [solidColoredLight](std::shared_ptr<openGL::shaders::ShaderProgram> shader)
    {
        shader->set_vec4("lightColor", solidColoredLight->Color.PropertyValue);
    };

    // A couple test models using the factories...
    auto generate_model = [camera](const std::shared_ptr<openGL::shaders::ShaderProgram>& shader,
                                   openGL::primitives::PrimitiveFactory::EPrimitiveType primitive_type,
                                   glm::vec3 dimensions, glm::vec4 default_color = glm::vec4(0.5f))
    {
      auto primitive = openGL::primitives::PrimitiveFactory::create_primitive(primitive_type, dimensions);
      primitive->Mesh.DefaultColor = default_color; // Set the default color for the primitive
      return std::make_shared<openGL::model::ModelBase>(primitive->Mesh, shader, camera);
    };

    auto generate_segmented_model = [camera](const std::shared_ptr<openGL::shaders::ShaderProgram>& shader,
                                             openGL::primitives::PrimitiveFactory::ESegmentedPrimitiveType
                                             primitive_type,
                                             glm::vec3 dimensions, glm::vec3 segments,
                                             glm::vec4 default_color = glm::vec4(0.5f))
    {
      auto primitive = openGL::primitives::PrimitiveFactory::create_segmented_primitive(
        primitive_type, dimensions, segments);
      primitive->Mesh.DefaultColor = default_color; // Set the default color for the primitive
      return std::make_shared<openGL::model::ModelBase>(primitive->Mesh, shader, camera);
    };

    auto grid_model = generate_segmented_model(defaultColouredVertexShader,
                                               openGL::primitives::PrimitiveFactory::GridLines,
                                               glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(11.0f, 11.0f, 11.0f),
                                               glm::vec4(0.1f));
    // grid_model->Orientation = glm::vec3{0.0f, 0.0f, -90.0f};
    // Rotate the grid by -90 degrees around the Z-axis so that it is horizontal
    core.addModel(grid_model);

    auto circle_model = generate_segmented_model(defaultColouredVertexShader,
                                                 openGL::primitives::PrimitiveFactory::Circle, glm::vec3(1.0f),
                                                 glm::vec3(32, 0, 0), glm::vec4(0.1f, 0.2, 0.3, 1.0));
    circle_model->Position = glm::vec3(-2.0f, 2.0f, -3.0f);
    circle_model->Scale = glm::vec3(1.2f);
    core.addModel(circle_model);

    auto plane_model = generate_segmented_model(defaultColouredVertexShader,
                                                openGL::primitives::PrimitiveFactory::Plane,
                                                glm::vec3(2.0f, 2.0f, 0.0f), glm::vec3(1, 1, 0), glm::vec4(0.5f, 0.2, 0.7, 1.0));
    plane_model->Position = glm::vec3(0.0f, -2.0f, 0.0f);
    plane_model->Orientation = glm::vec3(90.0f, 0.0f, 0.0f);
    core.addModel(plane_model);

    auto triangle_Model = generate_model(defaultColouredVertexShader, openGL::primitives::PrimitiveFactory::Triangle,
                                         glm::vec3(1.0f), glm::vec4(0.1f, 0.1, 0.7, 1.0));
    triangle_Model->Position = glm::vec3(-2.0f, 2.0f, -4.0f);
    core.addModel(triangle_Model);

    auto cube_model = generate_model(texturedVertexShader, openGL::primitives::PrimitiveFactory::Cube, glm::vec3(1.0f), glm::vec4(0.1f, 0.2, 0.3, 1.0));
    cube_model->set_texture_from_file("./res/textures/container.jpg");
    cube_model->set_texture_from_file("./res/textures/awesomeface.jpg");
    core.addModel(cube_model);

    auto sphere_model = generate_segmented_model(lightedColouredVertexShader,
                                                 openGL::primitives::PrimitiveFactory::UVSphere, glm::vec3(2.0f),
                                                 glm::vec3(12, 12, 0), glm::vec4(1.0f, 1.0, 1.0, 1.0));
    sphere_model->Position += glm::vec3(2.0f, 2.0f, -3.0f);
    sphere_model->Scale = glm::vec3(0.5f, 0.5f, 0.5f);
    core.addModel(sphere_model);

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
