#pragma once
#include "TEntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyId :
    public TEntityPropertyBase<EntityPropertyId, unsigned int>
  {
  public:
    EntityPropertyId() = default;

    EntityPropertyId(const unsigned& property_value)
      : TEntityPropertyBase(property_value)
    {
    }
  };
}
