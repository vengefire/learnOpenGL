#pragma once

#include "PrimitiveBase.h"
#include "../entity/property/EntityPropertyDimensions.h"
#include "../learnOpenGL/openGL/mesh/base/VertexBase.h"
#include "../mesh/base/MeshBase.h"

namespace openGL::primitives
{
  template <class TDerived>
  class TypedPrimitiveBase : public PrimitiveBase
  {
  public:
    TypedPrimitiveBase(const entity::property::EntityPropertyDimensions& dimensions)
      : PrimitiveBase(dimensions)
    {
    }

    ~TypedPrimitiveBase() override = default;

    const mesh::MeshBase& Generate()
    {
      Mesh = generate_primitive_mesh();
      return Mesh;
    }

    static TDerived& generate_primitive(TDerived& primitive)
    {
      primitive.Generate();
      return primitive;
    }
  };
}
