#pragma once
#include "PrimitiveBase.h"

namespace openGL::primitives
{
  class TrianglePrimitive :
    public TypedPrimitiveBase<TrianglePrimitive>
  {
  public:
    TrianglePrimitive(entity::property::EntityPropertyDimensions dimensions)
      : TypedPrimitiveBase(dimensions)
    {
    }

    static TrianglePrimitive& generate_triangle(float width, float height, float depth = 0.0f)
    {
      auto trianglePrimitive = TrianglePrimitive(glm::vec3{width, height, depth});
      TypedPrimitiveBase::generate_primitive(trianglePrimitive);
      return trianglePrimitive;
    }

    mesh::MeshBase generate_primitive_mesh() override
    {
      _vertices.clear();
      _indices.clear();
      auto normal = glm::vec3(0.0f, 0.0f, 1.0f); // Normal pointing up in Z direction
      _vertices.emplace_back(-Dimensions.Width / 2.0f, -Dimensions.Height / 2.0f, 0.0f, 0.0f, 0.0f, normal.x, normal.y, normal.z); // Bottom left
      _vertices.emplace_back(Dimensions.Width / 2.0f, -Dimensions.Height / 2.0f, 0.0f, 1.0f, 0.0f, normal.x, normal.y, normal.z);  // Bottom right
      _vertices.emplace_back(0.0f, Dimensions.Height / 2.0f, 0.0f, 0.5f, 1.0f, normal.x, normal.y, normal.z);           // Top
      return { _vertices, _indices };
    }
  };
}
