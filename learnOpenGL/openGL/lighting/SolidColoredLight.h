#pragma once
#include "../entity/property/EntityPropertyColor.h"
#include "base/LightBase.h"

namespace openGL::lighting
{
  class SolidColoredLight :
    public LightBase
  {
  public:
    SolidColoredLight(const entity::property::EntityPropertyColor& color) : color_(color)
    {
    }

  protected:
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
}
