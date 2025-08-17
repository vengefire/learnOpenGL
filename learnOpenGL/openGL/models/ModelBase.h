#pragma once

#include "../../config.h"
#include "../shaders/ShaderProgram.h"
#include "../textures/TextureBase.h"
#include "../core/VertexBase.h"

namespace openGL::models
{
  class ModelBase
  {
  public:
    ModelBase();
    virtual ~ModelBase();

    std::vector<float> get_vertices() const;

    std::shared_ptr<shaders::ShaderProgram> get_shader_program() const
    {
      return shader_program_;
    }

    void set_texture_from_file(const std::string& textureFilePath);

    void set_shader_program(std::shared_ptr<shaders::ShaderProgram> shader_program)
    {
      shader_program_ = shader_program;
    }

    std::vector<std::shared_ptr<textures::TextureBase>> get_textures() const
    {
      return textures_;
    };

    void set_texture(const std::shared_ptr<textures::TextureBase>& texture)
    {
      textures_.push_back(texture);
    }

    void set_vertices(std::vector<float> vertices);
    void set_vertices(std::vector<core::VertexBase> vertices);
    void set_indices(std::vector<unsigned int> indices);

    void render();

  protected:
    void buffer_vertex_data();

  private:
    void Init();
    std::shared_ptr<shaders::ShaderProgram> shader_program_;
    std::vector<std::shared_ptr<textures::TextureBase>> textures_;
    std::vector<core::VertexBase> vertices_data_;
    std::vector<float> vertices_;
    std::vector<unsigned int> indices_;
    unsigned int vao_Id_ = -1;
    unsigned int vbo_Id_ = -1;
    unsigned int ebo_Id_ = -1;
  };
}
