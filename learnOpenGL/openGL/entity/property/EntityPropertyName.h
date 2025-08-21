#pragma once
#include <string>

#include "EntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyName :
    public EntityPropertyBase<std::string>
  {
  public:
    EntityPropertyName() = default;

    EntityPropertyName(const std::string& property_value)
      : EntityPropertyBase<std::string>(property_value)
    {
    }

    ~EntityPropertyName() = default;
  };
}
