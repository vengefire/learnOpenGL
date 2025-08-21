#pragma once
#include "TypedPrimitiveBase.h"

namespace openGL::primitives
{
  class PlanePrimitive : public SegmentedTypedPrimitiveBase<PlanePrimitive>
  {
  public:
    PlanePrimitive(const entity::property::EntityPropertyDimensions& dimensions,
      const entity::property::EntityPropertyDimensions& segments)
      : SegmentedTypedPrimitiveBase<PlanePrimitive>(dimensions, segments)
    {
    }

    PlanePrimitive(float width, float height, unsigned int widthSegments = 1, unsigned int heightSegments = 1) :
      SegmentedTypedPrimitiveBase(glm::vec3(width, height, 0.0f), glm::vec3(widthSegments, heightSegments, 0))
    {
    }

    static PlanePrimitive generate_plane(float width, float height, unsigned int widthSegments = 1,
      unsigned int heightSegments = 1)
    {
      auto planePrimitive = PlanePrimitive(width, height, widthSegments, heightSegments);
      TypedPrimitiveBase::generate_primitive(planePrimitive);
      return planePrimitive;
    }

    mesh::MeshBase generate_primitive_mesh() override
    {
      _vertices.clear();
      _indices.clear();
      float halfWidth = Dimensions.Width / 2.0f;
      float halfHeight = Dimensions.Height / 2.0f;
      for (unsigned int y = 0; y <= Segments.Height; ++y)
      {
        for (unsigned int x = 0; x <= Segments.Width; ++x)
        {
          float posX = -halfWidth + (static_cast<float>(x) / Segments.Width) * Dimensions.Width;
          float posY = -halfHeight + (static_cast<float>(y) / Segments.Height) * Dimensions.Height;
          _vertices.emplace_back(posX, posY, 0.0f);
        }
      }
      for (unsigned int y = 0; y < Segments.Height; ++y)
      {
        for (unsigned int x = 0; x < Segments.Width; ++x)
        {
          unsigned int topLeft = y * (Segments.Width + 1) + x;
          unsigned int topRight = topLeft + 1;
          unsigned int bottomLeft = topLeft + (Segments.Width + 1);
          unsigned int bottomRight = bottomLeft + 1;
          _indices.push_back(topLeft);
          _indices.push_back(bottomLeft);
          _indices.push_back(topRight);
          _indices.push_back(topRight);
          _indices.push_back(bottomLeft);
          _indices.push_back(bottomRight);
        }
      }
      return { _vertices, _indices, };
    }

    unsigned int width_segments_;
    unsigned int height_segments_;
  };
}
