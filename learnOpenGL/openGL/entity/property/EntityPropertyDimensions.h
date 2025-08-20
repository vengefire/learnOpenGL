#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include "EntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyDimensions : public openGl::entity::property::EntityPropertyBase<glm::vec3>
  {
  public:
    explicit EntityPropertyDimensions(const glm::vec3& dimensions)
      : EntityPropertyBase(dimensions)
    {
    }
  };

}
