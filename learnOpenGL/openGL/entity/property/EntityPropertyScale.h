#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>

#include "EntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyScale : public openGl::entity::property::EntityPropertyBase<glm::vec3>
  {
  public:
    EntityPropertyScale(const glm::vec3& scale)
      : EntityPropertyBase(scale)
    {
    }
  };
}
