#pragma once

#include "../../config.h"
#include "../shaders/ShaderProgram.h"
#include "../textures/TextureBase.h"
#include "../core/VertexBase.h"
#include "../Events/ProcessInputEvent.h"
#include "../../framework/events/TEventSubscriberBase.h"
#include "../camera/CameraBase.h"

namespace openGL::models
{
  class ModelBase
    : public framework::events::TEventSubscriberBase<events::ProcessInputEventData>
  {
  public:
    ModelBase();
    ModelBase(std::shared_ptr<shaders::ShaderProgram> shaderProgram);
    ~ModelBase() override;

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

    void set_camera(std::shared_ptr<camera::CameraBase> camera)
    {
      camera_ = camera;
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

  public:
    [[nodiscard]] float get_rotation_x() const
    {
      return rotationX_;
    }

    void set_rotation_x(float rotation_x)
    {
      rotationX_ = rotation_x;
    }

    __declspec(property(get = get_rotation_x, put = set_rotation_x)) float RotationX;

  private:
    std::shared_ptr<camera::CameraBase> camera_;
    float rotationY_ = 0.0f;
    float rotationZ_ = 0.0f;
    // Translation values
    float translationX_ = 0.0f;
    float translationY_ = 0.0f;
    float translationZ_ = 0.0f;
  };
}
