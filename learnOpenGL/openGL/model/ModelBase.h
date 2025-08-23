#pragma once
#include <memory>

#include "../camera/CameraBase.h"
#include "../shaders/ShaderProgram.h"
#include "../mesh/base/MeshBase.h"
#include "../textures/TextureBase.h"

namespace openGL::model
{
  class ModelBase
  {
  public:
    ModelBase() = default;
    ModelBase(mesh::MeshBase mesh, const std::shared_ptr<shaders::ShaderProgram>& shader_program,
              const std::shared_ptr<camera::CameraBase>& camera);

    void renderModel();

  protected:
    virtual ~ModelBase();

    unsigned int vao_id_ = 0, vbo_id_ = 0, ebo_id_ = 0;
    std::shared_ptr<shaders::ShaderProgram> shader_program_;
    std::shared_ptr<camera::CameraBase> camera_;
    mesh::MeshBase mesh_;
    std::vector<std::shared_ptr<textures::TextureBase>> textures_;

    virtual glm::mat4 calculate_translation() = 0;

    // REFACTOR
  public:
    void set_texture_from_file(const std::string& textureFilePath, bool flip_vertically = true);
    void set_texture(const std::shared_ptr<textures::TextureBase>& texture);

    [[nodiscard]] mesh::MeshBase mesh() const
    {
      return mesh_;
    }

    __declspec(property(get = mesh, put = set_mesh)) mesh::MeshBase Mesh;

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
