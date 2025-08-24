#pragma once
#include <glm/detail/type_vec.hpp>

#include "TEntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyColor :
    public TEntityPropertyBase<glm::vec4>
  {
  public:
    EntityPropertyColor() = default;
    EntityPropertyColor(const glm::vec4& color) : TEntityPropertyBase(color)
    {
    }

    float R()
    {
      return PropertyValue.x;
    }

    float G()
    {
      return PropertyValue.y;
    }

    float B()
    {
      return PropertyValue.z;
    }

    float A()
    {
      return PropertyValue.w;
    }
  };
}
