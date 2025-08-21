#pragma once

namespace framework::property
{

  // PropertyBaseMorphOperands is a base class for properties that can be morphed or transformed.
  template <class TDerived, class TProperty>
  class PropertyBaseMorphOperands
  {
  public:
    // Allow derived classes to access the property value directly
    friend TDerived& operator += (TDerived& lhs, const TProperty& rhs)
    {
      lhs.PropertyValue += rhs;
      return lhs;
    }

    friend TDerived operator + (TDerived lhs, const TProperty& rhs)
    {
      lhs.PropertyValue += rhs;
      return lhs;
    }
  };

}