#pragma once
#include "TypedPrimitiveBase.h"

namespace openGL::primitives
{
  template <class TDerived>
  class SegmentedTypedPrimitiveBase : public TypedPrimitiveBase<TDerived>
  {
  public:
    SegmentedTypedPrimitiveBase(const entity::property::EntityPropertyDimensions& dimensions,
                                const entity::property::EntityPropertyDimensions& segments)
      : TypedPrimitiveBase<TDerived>(dimensions)
    {
      Segments = segments;
    }

  protected:
    entity::property::EntityPropertyDimensions segments_;

    [[nodiscard]] entity::property::EntityPropertyDimensions segments() const
    {
      return segments_;
    }

    void set_segments(const entity::property::EntityPropertyDimensions& segments)
    {
      segments_ = segments;
    }

    __declspec(property(get = segments, put = set_segments)) entity::property::EntityPropertyDimensions Segments;
  };
}
