#pragma once
#include "TEntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyId :
    public TEntityPropertyBase<unsigned int>
  {
  public:
    EntityPropertyId() = default;

    EntityPropertyId(const unsigned& property_value)
      : TEntityPropertyBase<unsigned>(property_value)
    {
    }
  };
}
