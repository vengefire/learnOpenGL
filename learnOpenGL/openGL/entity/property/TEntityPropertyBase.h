#pragma once

#include "../../../framework/property/TPropertyBaseMorphOperands.h"
#include "../../learnOpenGL/framework/property/TPropertyBase.h"

namespace openGL::entity::property
{
  template <class TDerivedEntity, class TEntityProperty>
  class TEntityPropertyBase :
    public framework::property::TPropertyBase<TEntityProperty>,
    public framework::property::TPropertyBaseMorphOperands<TDerivedEntity, TEntityProperty>
  {
  public:
    TEntityPropertyBase() : framework::property::TPropertyBase<TEntityProperty>()
    {
    }
    TEntityPropertyBase(const TEntityProperty& property_value) : framework::property::TPropertyBase<TEntityProperty>(property_value)
    {}
  };
}
