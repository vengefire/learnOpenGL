#pragma once

#include "../../config.h"
#include "../shaders/ShaderProgram.h"
#include "../textures/TextureBase.h"
#include "../core/VertexBase.h"
#include "../Events/ProcessInputEvent.h"
#include "../../framework/events/TEventSubscriberBase.h"

namespace openGL::models
{
  class ModelBase
    : public framework::events::TEventSubscriberBase<events::ProcessInputEventData>
  {
  public:
    ModelBase();
    virtual ~ModelBase();

    std::vector<float> get_vertices() const;

    std::shared_ptr<shaders::ShaderProgram> get_shader_program() const
    {
      return shader_program_;
    }

    void set_texture_from_file(const std::string& textureFilePath, bool flip_vertically = true);

    void set_shader_program(std::shared_ptr<shaders::ShaderProgram> shader_program)
    {
      shader_program_ = shader_program;
    }

    std::vector<std::shared_ptr<textures::TextureBase>> get_textures() const
    {
      return textures_;
    };

    std::shared_ptr<textures::TextureBase> get_texture(unsigned int index) const
    {
      if (index < textures_.size())
      {
        return textures_[index];
      }
      return nullptr;
    }

    void set_texture(const std::shared_ptr<textures::TextureBase>& texture)
    {
      textures_.push_back(texture);
    }

    void set_vertices(std::vector<core::VertexBase> vertices);
    void set_indices(std::vector<unsigned int> indices);

    void render();

  protected:
    void buffer_vertex_data();

  private:
    void Init();

  public:
    void handle_event(events::ProcessInputEventData* pEventData) override;

  private:
    std::shared_ptr<shaders::ShaderProgram> shader_program_;
    std::vector<std::shared_ptr<textures::TextureBase>> textures_;
    std::vector<core::VertexBase> vertices_data_;
    std::vector<float> vertices_;
    std::vector<unsigned int> indices_;
    unsigned int vao_Id_ = -1;
    unsigned int vbo_Id_ = -1;
    unsigned int ebo_Id_ = -1;

    float textureMix_ = 0.02f;
    // Scale value
    float scale_ = 1.0f;
    // Rotation values
    float rotationX_ = 0.0f;
    float rotationY_ = 0.0f;
    float rotationZ_ = 0.0f;
    // Translation values
    float translationX_ = 0.0f;
    float translationY_ = 0.0f;
    float translationZ_ = 0.0f;
  };
}
