#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/vec4.hpp>

#include "TEntityPropertyBase.h"
#include "../../../framework/property/PropertyBaseMorphOperands.h"

namespace openGL::entity::property
{
  class EntityPropertyColor :
    public TEntityPropertyBase<glm::vec4>,
    public framework::property::PropertyBaseMorphOperands<EntityPropertyColor, glm::vec3>
  {
  public:
    EntityPropertyColor() = default;
    EntityPropertyColor(const glm::vec4& color) : TEntityPropertyBase(color)
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
