#pragma once
#include "../entity/property/EntityPropertyColor.h"
#include "base/LightModelBase.h"

namespace openGL::lighting
{
  class SolidColoredLight :
    public LightModelBase
  {
  public:
    SolidColoredLight(const entity::property::EntityPropertyColor& color, const mesh::MeshBase& mesh, const std::shared_ptr<shaders::ShaderProgram>& shader,
      const std::shared_ptr<camera::CameraBase>& camera)
      : LightModelBase(mesh, shader, camera)
        , color_(color)
    {
    }

    ~SolidColoredLight() override = default;

  protected:
    glm::mat4 calculate_translation() override;

    entity::property::EntityPropertyColor color_{ glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) };

  public:
    [[nodiscard]] entity::property::EntityPropertyColor color() const
    {
      return color_;
    }

    void set_color(const entity::property::EntityPropertyColor& color)
    {
      color_ = color;
    }

    __declspec(property(get = color, put = set_color)) entity::property::EntityPropertyColor Color;
  };

  inline glm::mat4 SolidColoredLight::calculate_translation()
  {
    return LightModelBase::calculate_translation();
  }
}
