#pragma once
#include "PrimitiveBase.h"

namespace openGL::primitives
{
  class TrianglePrimitive :
    public PrimitiveBase
  {
  public:
    TrianglePrimitive(float width, float height, float depth)
      : PrimitiveBase(width, height, depth)
    {
      generate_primitive();
    }

    void generate_primitive() override;
    static TrianglePrimitive generate_triangle(float width, float height, float depth = 0.0f)
    {
      return { width, height, depth };
    }
  };

  inline void TrianglePrimitive::generate_primitive()
  {
    _vertices.clear();
    _indices.clear();
    // Define the vertices of the triangle
    _vertices.emplace_back(-_width / 2.0f, -_height / 2.0f, 0.0f, 0.0f, 0.0f); // Bottom left
    _vertices.emplace_back(_width / 2.0f, -_height / 2.0f, 0.0f, 1.0f, 0.0f);  // Bottom right
    _vertices.emplace_back(0.0f, _height / 2.0f, 0.0f, 0.5f, 1.0f);           // Top
    // Define the indices for the triangle
    //_indices = { 0, 1, 2 };
  }
}
