#pragma once
#include "TypedPrimitiveBase.h"

namespace openGL::primitives
{
  template <class TDerived>
  class CartesianPrimitiveBase :
    public TypedPrimitiveBase<TDerived>
  {
  public:
    explicit CartesianPrimitiveBase(const entity::property::EntityPropertyDimensions& dimensions)
      : TypedPrimitiveBase<TDerived>(dimensions)
    {
    }
  };
}
