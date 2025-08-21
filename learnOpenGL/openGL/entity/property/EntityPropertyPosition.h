#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include "EntityPropertyBase.h"

namespace openGL::entity::property
{
  // EntityPropertyPosition is a base class for entities that have a position in 3D space.
  class EntityPropertyPosition :
    public openGl::entity::property::EntityPropertyBase<glm::vec3>,
    public framework::property::PropertyBaseMorphOperands<EntityPropertyPosition, glm::vec3>
  {
  public:
    EntityPropertyPosition() = default;
    EntityPropertyPosition(const glm::vec3& position)
      : EntityPropertyBase(position)
    {
    }
    EntityPropertyPosition(float x, float y, float z)
      : EntityPropertyBase(glm::vec3(x, y, z))
    {
    }
  };
}
