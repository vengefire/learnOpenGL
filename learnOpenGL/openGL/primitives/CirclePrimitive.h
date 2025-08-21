#pragma once
#include "SegmentedTypedPrimitiveBase.h"
#include "TypedPrimitiveBase.h"

namespace openGL::primitives
{
  class CirclePrimitive : public SegmentedTypedPrimitiveBase<CirclePrimitive>
  {
  public:
    CirclePrimitive(const entity::property::EntityPropertyDimensions& dimensions,
                    const entity::property::EntityPropertyDimensions& segments)
      : SegmentedTypedPrimitiveBase<CirclePrimitive>(dimensions, segments)
    {
    }

    CirclePrimitive(float radius = 1.0f, unsigned int segments = 32)
      : CirclePrimitive(glm::vec3{radius * 2.0f, radius * 2.0f, radius}, glm::vec3{segments, 0.0f, 0.0f})
    {
    }

    static CirclePrimitive generate_circle(float radius = 1.0f, unsigned int segments = 32)
    {
      if (radius <= 0.0f)
      {
        throw std::invalid_argument("Radius must be greater than zero.");
      }

      if (segments < 3)
      {
        throw std::invalid_argument("Segments must be at least 3.");
      }

      auto circle_primitive = CirclePrimitive(radius, segments);
      return generate_primitive(circle_primitive);
    }

  protected:
    mesh::MeshBase generate_primitive_mesh() override
    {
      _vertices.clear();
      _indices.clear();
      // Generate vertices for the circle
      float radius = Dimensions.Depth / 2.0f; // Assuming Depth is the radius
      unsigned int segments = static_cast<unsigned int>(Segments.Width); // Assuming Width is the number of segments
      _vertices.emplace_back(0.0f, 0.0f, 0.0f, (0 / radius + 1.0f) / 2.0f, (0 / radius + 1.0f) / 2.0f);
      for (unsigned int i = 0; i <= segments; ++i)
      {
        float angle = 2.0f * glm::pi<float>() * static_cast<float>(i) / static_cast<float>(segments);
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        _vertices.emplace_back(x, y, 0.0f, (x / radius + 1.0f) / 2.0f, (y / radius + 1.0f) / 2.0f);
      }
      // Generate indices for the circle
      for (unsigned int i = 1; i <= segments; ++i)
      {
        _indices.push_back(0); // Center vertex
        _indices.push_back(i);
        _indices.push_back((i % segments) + 1); // Wrap around to the first vertex
      }

      return {_vertices, _indices};
    }
  };
}
