#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include "TEntityPropertyBase.h"

namespace openGL::entity::property
{
  // EntityPropertyPosition is a base class for entities that have a position in 3D space.
  class EntityPropertyPosition :
    public TEntityPropertyBase<glm::vec3>,
    public framework::property::PropertyBaseMorphOperands<EntityPropertyPosition, glm::vec3>
  {
  public:
    EntityPropertyPosition() = default;
    EntityPropertyPosition(const glm::vec3& position)
      : TEntityPropertyBase(position)
    {
    }
    EntityPropertyPosition(float x, float y, float z)
      : TEntityPropertyBase(glm::vec3(x, y, z))
    {
    }
  };
}
