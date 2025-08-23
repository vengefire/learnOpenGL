#pragma once

#include "../../learnOpenGL/framework/property/PropertyBase.h"

namespace openGL::entity::property
{
  template <class TEntityProperty>
  class TEntityPropertyBase :
    public framework::property::PropertyBase<TEntityProperty>
  {
  public:
    TEntityPropertyBase() : framework::property::PropertyBase<TEntityProperty>()
    {
    }
    TEntityPropertyBase(const TEntityProperty& property_value) : framework::property::PropertyBase<TEntityProperty>(property_value)
    {}
  };
}
