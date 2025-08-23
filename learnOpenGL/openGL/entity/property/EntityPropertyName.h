#pragma once
#include <string>

#include "TEntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyName :
    public TEntityPropertyBase<std::string>
  {
  public:
    EntityPropertyName() = default;

    EntityPropertyName(const std::string& property_value)
      : TEntityPropertyBase<std::string>(property_value)
    {
    }

    ~EntityPropertyName() = default;
  };
}
