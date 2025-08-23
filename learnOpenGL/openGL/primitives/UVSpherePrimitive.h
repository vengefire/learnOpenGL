#pragma once
#include <glm/gtc/constants.hpp>

#include "PrimitiveBase.h"

namespace openGL::primitives
{
  class UVSpherePrimitive :
    public SegmentedTypedPrimitiveBase<UVSpherePrimitive>
  {
  public:
    UVSpherePrimitive(const entity::property::EntityPropertyDimensions& dimensions,
      const entity::property::EntityPropertyDimensions& segments)
      : SegmentedTypedPrimitiveBase<UVSpherePrimitive>(dimensions, segments)
    {
    }

    UVSpherePrimitive(float rings, float sectors, float radius)
      : UVSpherePrimitive(glm::vec3{ radius * 2, radius * 2, radius *2 }, glm::vec3(rings, sectors, radius))
    {
    }

    static UVSpherePrimitive generate_uv_sphere(float width, float height, float depth)
    {
      auto uvSpherePrimitive = UVSpherePrimitive(width, height, depth);
      TypedPrimitiveBase::generate_primitive(uvSpherePrimitive);
      return uvSpherePrimitive;
    }

    mesh::MeshBase generate_primitive_mesh() override
    {
      _vertices.clear();
      _indices.clear();
      const unsigned int rings = Segments.Height; // Number of horizontal segments
      const unsigned int sectors = Segments.Width; // Number of vertical segments
      const float radius = Dimensions.Depth / 2.0f;
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

          float normalx = sinPhi * cosTheta;
          float normaly = sinPhi * sinTheta;
          float normalz = cosPhi;

          _vertices.emplace_back(x, y, z, u, v, normalx, normaly, normalz);
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
      return { _vertices, _indices };
    }
  };
}
