#pragma once
#include <glm/gtc/constants.hpp>

#include "PrimitiveBase.h"

namespace openGL::primitives
{
  class UVSpherePrimitive :
    public PrimitiveBase
  {
  public:
    UVSpherePrimitive(float width, float height, float depth)
      : PrimitiveBase(width, height, depth)
    {
      UVSpherePrimitive::generate_primitive();
    }

    void generate_primitive() override;

    static UVSpherePrimitive generate_uv_sphere(float width, float height, float depth)
    {
      return {width, height, depth};
    }
  };

  inline void UVSpherePrimitive::generate_primitive()
  {
    _vertices.clear();
    _indices.clear();
    const unsigned int rings = _height; // Number of horizontal segments
    const unsigned int sectors = _width; // Number of vertical segments
    const float radius = _depth / 2.0f;
    for (unsigned int r = 0; r <= rings; ++r)
    {
      float theta = r * glm::pi<float>() / rings; // Vertical angle
      float sinTheta = sin(theta);
      float cosTheta = cos(theta);
      for (unsigned int s = 0; s <= sectors; ++s)
      {
        float phi = s * 2.0f * glm::pi<float>() / sectors; // Horizontal angle
        float sinPhi = sin(phi);
        float cosPhi = cos(phi);
        // Vertex position
        float x = radius * cosPhi * sinTheta;
        float y = radius * cosTheta;
        float z = radius * sinPhi * sinTheta;
        // Texture coordinates
        float u = -static_cast<float>(s) / sectors;
        float v = -static_cast<float>(r) / rings;
        _vertices.emplace_back(x, y, z, u, v);
      }
    }

    for (unsigned int r = 0; r < rings; ++r)
    {
      for (unsigned int s = 0; s < sectors; ++s)
      {
        unsigned int first = (r * (sectors + 1)) + s;
        unsigned int second = first + sectors + 1;
        _indices.push_back(first);
        _indices.push_back(second);
        _indices.push_back(first + 1);
        _indices.push_back(second);
        _indices.push_back(second + 1);
        _indices.push_back(first + 1);
      }
    }
  }
}
