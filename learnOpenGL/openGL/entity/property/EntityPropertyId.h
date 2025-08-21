#pragma once
#include "EntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyId :
    public EntityPropertyBase<unsigned int>
  {
  public:
    EntityPropertyId() = default;

    EntityPropertyId(const unsigned& property_value)
      : EntityPropertyBase<unsigned>(property_value)
    {
    }
  };
}
