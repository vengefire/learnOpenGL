#pragma once
#include <memory>

#include "../camera/CameraBase.h"
#include "../shaders/ShaderProgram.h"
#include "../mesh/base/MeshBase.h"
#include "../textures/TextureBase.h"

#include "../entity/property/EntityPropertyPosition.h"
#include "../entity/property/EntityPropertyOrientation.h"
#include "../entity/property/EntityPropertyScale.h"

namespace openGL::model
{
  class ModelBase
  {
  public:
    ModelBase() = default;
    ModelBase(mesh::MeshBase mesh, const std::shared_ptr<shaders::ShaderProgram>& shader_program,
              const std::shared_ptr<camera::CameraBase>& camera);

    ~ModelBase();

    void renderModel();

  protected:
    unsigned int vao_id_ = 0, vbo_id_ = 0, ebo_id_ = 0;
    std::shared_ptr<shaders::ShaderProgram> shader_program_;
    std::shared_ptr<camera::CameraBase> camera_;
    mesh::MeshBase mesh_;
    std::vector<std::shared_ptr<textures::TextureBase>> textures_;
    entity::property::EntityPropertyPosition position_;
    entity::property::EntityPropertyOrientation orientation_;
    entity::property::EntityPropertyScale scale_;

    // REFACTOR
  public:
    bool draw_lines_ = false;
    void set_texture_from_file(const std::string& textureFilePath, bool flip_vertically = true);
    void set_texture(const std::shared_ptr<textures::TextureBase>& texture);

    [[nodiscard]] bool draw_lines() const
    {
      return draw_lines_;
    }

    void set_draw_lines(const bool draw_lines)
    {
      draw_lines_ = draw_lines;
    }

    __declspec(property(get = draw_lines, put = set_draw_lines)) bool DrawLines;

    [[nodiscard]] entity::property::EntityPropertyPosition position() const
    {
      return position_;
    }

    void set_position(const entity::property::EntityPropertyPosition& position)
    {
      position_ = position;
    }

    __declspec(property(get = position, put = set_position)) entity::property::EntityPropertyPosition Position;

    [[nodiscard]] entity::property::EntityPropertyOrientation orientation() const
    {
      return orientation_;
    }

    void set_rotation(const entity::property::EntityPropertyOrientation& orientation)
    {
      orientation_ = orientation;
    }

    __declspec(property(get = orientation, put = set_rotation)) entity::property::EntityPropertyOrientation Orientation;

    [[nodiscard]] entity::property::EntityPropertyScale scale() const
    {
      return scale_;
    }

    void set_scale(const entity::property::EntityPropertyScale& scale)
    {
      this->scale_ = scale;
    }

    __declspec(property(get = scale, put = set_scale)) entity::property::EntityPropertyScale Scale;

    [[nodiscard]] mesh::MeshBase mesh1() const
    {
      return mesh_;
    }

    __declspec(property(get = mesh1, put = set_mesh)) mesh::MeshBase Mesh;

    [[nodiscard]] std::shared_ptr<shaders::ShaderProgram> shader_program() const
    {
      return shader_program_;
    }

    void set_shader_program(const std::shared_ptr<shaders::ShaderProgram>& shader_program)
    {
      shader_program_ = shader_program;
    }

    __declspec(property(get = shader_program, put = set_shader_program)) std::shared_ptr<shaders::ShaderProgram>
    ShaderProgram;

    [[nodiscard]] std::shared_ptr<camera::CameraBase> camera1() const
    {
      return camera_;
    }

    void set_camera(const std::shared_ptr<camera::CameraBase>& camera)
    {
      camera_ = camera;
    }

    __declspec(property(get = camera1, put = set_camera)) std::shared_ptr<camera::CameraBase> Camera;

  private:
    void initialize_buffers();
    void upload_vertex_data() const;
    void configure_vertex_attributes();
    void upload_indices_data();
    void set_mesh(const mesh::MeshBase& mesh);
  };
}
