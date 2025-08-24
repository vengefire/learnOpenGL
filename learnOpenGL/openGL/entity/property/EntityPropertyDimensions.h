#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include "TEntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyDimensions : public TEntityPropertyBase<glm::vec3>
  {
  public:
    EntityPropertyDimensions() = default;
    EntityPropertyDimensions(const glm::vec3& dimensions)
      : TEntityPropertyBase(dimensions)
    {
    }

    float get_width() 
    {
      return PropertyValue.x;
    }

    float get_height() 
    {
      return PropertyValue.y;
    }

    float get_depth() 
    {
      return PropertyValue.z;
    }

    __declspec(property(get = get_width)) float Width;
    __declspec(property(get = get_height)) float Height;
    __declspec(property(get = get_depth)) float Depth;
  };
}
