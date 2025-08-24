#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>

#include "TEntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyScale : public TEntityPropertyBase<glm::vec3>
  {
  public:
    EntityPropertyScale() = default;
    EntityPropertyScale(const glm::vec3& scale)
      : TEntityPropertyBase(scale)
    {
    }
  };
}
