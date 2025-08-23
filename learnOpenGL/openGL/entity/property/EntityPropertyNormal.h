#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/vec3.hpp>

#include "TEntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyNormal : public TEntityPropertyBase<glm::vec3>
  {
  public:
    EntityPropertyNormal() = default;
    EntityPropertyNormal(const glm::vec3& property_value)
      : TEntityPropertyBase(property_value)
    {
    }

    float x() const
    {
      return PropertyValue.x;
    }

    float y() const
    {
      return PropertyValue.y;
    }

    float z() const
    {
      return PropertyValue.z;
    }

    __declspec(property(get = x)) float X;
    __declspec(property(get = y)) float Y;
    __declspec(property(get = z)) float Z;
  };
}
