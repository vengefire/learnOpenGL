#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include "EntityPropertyBase.h"

namespace openGL::entity::property
{
  // EntityPropertyPosition is a base class for entities that have a position in 3D space.
  class EntityPropertyPosition : public openGl::entity::property::EntityPropertyBase<glm::vec3>
  {
  public:
    EntityPropertyPosition(const glm::vec3& position)
      : EntityPropertyBase(position)
    {
    }
  };
}
