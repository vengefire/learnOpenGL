#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/vec3.hpp>

#include "EntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyNormal : public openGl::entity::property::EntityPropertyBase<glm::vec3>
  {
  public:
    EntityPropertyNormal() = default;
    EntityPropertyNormal(const glm::vec3& property_value)
      : EntityPropertyBase(property_value)
    {
    }
  };
}
