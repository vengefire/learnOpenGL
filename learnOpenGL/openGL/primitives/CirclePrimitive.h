#pragma once
#include "TypedPrimitiveBase.h"

namespace openGL::primitives
{
  class CirclePrimitive : public TypedPrimitiveBase<CirclePrimitive>
  {
  public:
    CirclePrimitive(float radius = 1.0f, unsigned int segments = 32)
      : TypedPrimitiveBase(glm::vec3{radius * 2.0f, radius * 2.0f, 0.0f}), radius_(radius), segments_(segments)
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
      return TypedPrimitiveBase::generate_primitive(circle_primitive);
    }

  protected:
    mesh::MeshBase generate_primitive_mesh() override
    {
      _vertices.clear();
      _indices.clear();
      // Generate vertices for the circle
      _vertices.emplace_back(0.0f, 0.0f, 0.0f, (0 / radius_ + 1.0f) / 2.0f, (0 / radius_ + 1.0f) / 2.0f);
      for (unsigned int i = 0; i <= segments_; ++i)
      {
        float angle = 2.0f * glm::pi<float>() * static_cast<float>(i) / static_cast<float>(segments_);
        float x = radius_ * cos(angle);
        float y = radius_ * sin(angle);
        _vertices.emplace_back(x, y, 0.0f, (x / radius_ + 1.0f) / 2.0f, (y / radius_ + 1.0f) / 2.0f);
      }
      // Generate indices for the circle
      for (unsigned int i = 1; i <= segments_; ++i)
      {
        _indices.push_back(0); // Center vertex
        _indices.push_back(i);
        _indices.push_back((i % segments_) + 1); // Wrap around to the first vertex
      }

      return { _vertices, _indices };
    }

  private:
    float radius_;
    unsigned int segments_;
  };
}
