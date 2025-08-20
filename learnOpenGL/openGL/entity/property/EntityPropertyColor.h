#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/vec4.hpp>

#include "EntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyColor :
    public openGl::entity::property::EntityPropertyBase<glm::vec4>
  {
  public:
    EntityPropertyColor() = default;

    EntityPropertyColor(const glm::vec4& color) : EntityPropertyBase(color)
    {
    }

    float R() const
    {
      return PropertyValue.x;
    }

    float G() const
    {
      return PropertyValue.y;
    }

    float B() const
    {
      return PropertyValue.z;
    }

    float A() const
    {
      return PropertyValue.w;
    }
  };
}
