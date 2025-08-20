#pragma once
#include "PrimitiveBase.h"

namespace openGL::primitives
{
  class CirclePrimitive : public PrimitiveBase
  {
  public:
    CirclePrimitive(float radius = 1.0f, unsigned int segments = 32)
      : PrimitiveBase(radius * 2.0f, radius * 2.0f, 0.0f), radius_(radius), segments_(segments)
    {
      CirclePrimitive::generate_primitive();
    }

    void generate_primitive() override;

    static CirclePrimitive generate_circle(float radius = 1.0f, unsigned int segments = 32)
    {
      return {radius, segments};
    }

  private:
    float radius_;
    unsigned int segments_;
  };

  inline void CirclePrimitive::generate_primitive()
  {
    _vertices.clear();
    _indices.clear();
    // Generate vertices for the circle
    _vertices.emplace_back(0, 0, 0.0f, (0 / radius_ + 1.0f) / 2.0f, (0 / radius_ + 1.0f) / 2.0f);
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
  }
}
