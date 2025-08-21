#pragma once

#include "../../learnOpenGL/framework/property/PropertyBase.h"

namespace openGL::entity::property
{
  template <class TEntityProperty>
  class EntityPropertyBase :
    public framework::property::PropertyBase<TEntityProperty>
  {
  public:
    EntityPropertyBase() : framework::property::PropertyBase<TEntityProperty>()
    {
    }
    EntityPropertyBase(const TEntityProperty& property_value) : framework::property::PropertyBase<TEntityProperty>(property_value)
    {}
  };
}
