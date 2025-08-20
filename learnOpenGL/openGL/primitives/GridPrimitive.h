#pragma once
#include "PrimitiveBase.h"

namespace openGL::primitives
{
  class GridPrimitive : public PrimitiveBase
  {
  public:
    GridPrimitive(float width, float height, float depth, float grid_line_spacing, bool centered)
      : PrimitiveBase(width, height, depth),
        grid_line_spacing_(grid_line_spacing),
        centered_(centered)
    {
      generate_grid_impl(_width, _height, _depth, grid_line_spacing_, centered_);
    }

    static GridPrimitive generate_grid_(float width, float height, float depth, float grid_line_spacing, bool centered)
    {
      return {width, height, depth, grid_line_spacing, centered};
    }

    void generate_primitive() override
    {
      openGL::primitives::GridPrimitive::generate_grid_impl(_width, _height, _depth, grid_line_spacing_, centered_);
    }

  private:
    GridPrimitive generate_grid_impl(float width, float height, float depth, float grid_line_spacing, bool centered)
    {
      _vertices.clear();
      _indices.clear();

      float halfWidth = width / 2.0f;
      float halfHeight = height / 2.0f;
      float halfDepth = depth / 2.0f;
      float width_excess = !centered ? 0.0f : fmod(halfWidth, grid_line_spacing);
      float height_excess = !centered ? 0.0f : fmod(halfHeight, grid_line_spacing);
      float depth_excess = !centered ? 0.0f : fmod(halfDepth, grid_line_spacing);

      glm::vec3 start = glm::vec3(-halfWidth + width_excess, -halfHeight + height_excess, -halfDepth + depth_excess);
      glm::vec3 end = glm::vec3(halfWidth - width_excess, halfHeight - height_excess, halfDepth - depth_excess);

      for (float z = start.z; z <= halfDepth; z += grid_line_spacing)
      {
        for (float x = start.x; x <= halfWidth; x += grid_line_spacing)
        {
          _vertices.emplace_back(x, -halfHeight, z);
          _vertices.emplace_back(x, halfHeight, z);
        }

        for (float y = start.y; y <= halfHeight; y += grid_line_spacing)
        {
          _vertices.emplace_back(-halfWidth, y, z);
          _vertices.emplace_back(halfWidth, y, z);
        }
      }

      for (float x = start.x; x <= halfWidth; x += grid_line_spacing)
      {
        for (float y = start.y; y <= halfHeight; y += grid_line_spacing)
        {
          _vertices.emplace_back(x, y, -halfDepth);
          _vertices.emplace_back(x, y, halfDepth);
        }
      }
      
      return *this;
    }
  private:
    float grid_line_spacing_;
    bool centered_;
  };
}
