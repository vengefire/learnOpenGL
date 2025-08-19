#pragma once
#include "PrimitiveBase.h"

namespace openGL::primitives
{
  class PlanePrimitive : public PrimitiveBase
  {
  public:
    void generate_primitive() override
    {
      generate_plane_impl(width_, height_, width_segments_, height_segments_);
    }

    PlanePrimitive(float width, float height, unsigned int widthSegments = 1, unsigned int heightSegments = 1) : width_(
      width), height_(height), width_segments_(widthSegments), height_segments_(heightSegments)
    {
      PlanePrimitive::generate_primitive();
    }

    static PlanePrimitive generate_plane(float width, float height, unsigned int widthSegments = 1,
                                         unsigned int heightSegments = 1)
    {
      PlanePrimitive plane(width, height, widthSegments, heightSegments);
      return plane;
    }

    void generate_plane_impl(float width, float height, unsigned int widthSegments = 1, unsigned int heightSegments = 1)
    {
      _vertices.clear();
      _indices.clear();
      float halfWidth = width / 2.0f;
      float halfHeight = height / 2.0f;
      for (unsigned int y = 0; y <= heightSegments; ++y)
      {
        for (unsigned int x = 0; x <= widthSegments; ++x)
        {
          float posX = -halfWidth + (static_cast<float>(x) / widthSegments) * width;
          float posY = -halfHeight + (static_cast<float>(y) / heightSegments) * height;
          _vertices.emplace_back(posX, posY, 0.0f);
        }
      }
      for (unsigned int y = 0; y < heightSegments; ++y)
      {
        for (unsigned int x = 0; x < widthSegments; ++x)
        {
          unsigned int topLeft = y * (widthSegments + 1) + x;
          unsigned int topRight = topLeft + 1;
          unsigned int bottomLeft = topLeft + (widthSegments + 1);
          unsigned int bottomRight = bottomLeft + 1;
          _indices.push_back(topLeft);
          _indices.push_back(bottomLeft);
          _indices.push_back(topRight);
          _indices.push_back(topRight);
          _indices.push_back(bottomLeft);
          _indices.push_back(bottomRight);
        }
      }
    }

    float width_;
    float height_;
    unsigned int width_segments_;
    unsigned int height_segments_;
  };
}
