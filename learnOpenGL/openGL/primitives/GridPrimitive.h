#pragma once
#include "TypedPrimitiveBase.h"

namespace openGL::primitives
{
  class GridPrimitive : public TypedPrimitiveBase<GridPrimitive>
  {
  public:

    GridPrimitive(entity::property::EntityPropertyDimensions dimensions, float grid_line_spacing, bool centered)
      : TypedPrimitiveBase(dimensions),
        grid_line_spacing_(grid_line_spacing),
        centered_(centered)
    {
    }

    static GridPrimitive generate_grid(float width, float height, float depth, float grid_line_spacing, bool centered)
    {
      auto gridPrimitive = GridPrimitive(
        glm::vec3{width, height, depth},
        grid_line_spacing,
        centered
      );
      gridPrimitive = TypedPrimitiveBase::generate_primitive(gridPrimitive);
      gridPrimitive.Mesh.DrawLines = true;
      return gridPrimitive;
    }

  protected:
    mesh::MeshBase generate_primitive_mesh() override
    {
      _vertices.clear();
      _indices.clear();

      float halfWidth = Dimensions.Width / 2.0f;
      float halfHeight = Dimensions.Height / 2.0f;
      float halfDepth = Dimensions.Depth / 2.0f;
      float width_excess = !centered_ ? 0.0f : fmod(halfWidth, grid_line_spacing_);
      float height_excess = !centered_ ? 0.0f : fmod(halfHeight, grid_line_spacing_);
      float depth_excess = !centered_ ? 0.0f : fmod(halfDepth, grid_line_spacing_);

      glm::vec3 start = glm::vec3(-halfWidth + width_excess, -halfHeight + height_excess, -halfDepth + depth_excess);
      glm::vec3 end = glm::vec3(halfWidth - width_excess, halfHeight - height_excess, halfDepth - depth_excess);

      for (float z = start.z; z <= halfDepth; z += grid_line_spacing_)
      {
        for (float x = start.x; x <= halfWidth; x += grid_line_spacing_)
        {
          _vertices.emplace_back(x, -halfHeight, z);
          _vertices.emplace_back(x, halfHeight, z);
        }

        for (float y = start.y; y <= halfHeight; y += grid_line_spacing_)
        {
          _vertices.emplace_back(-halfWidth, y, z);
          _vertices.emplace_back(halfWidth, y, z);
        }
      }

      for (float x = start.x; x <= halfWidth; x += grid_line_spacing_)
      {
        for (float y = start.y; y <= halfHeight; y += grid_line_spacing_)
        {
          _vertices.emplace_back(x, y, -halfDepth);
          _vertices.emplace_back(x, y, halfDepth);
        }
      }

      return { _vertices, _indices };
    }

  private:
    float grid_line_spacing_;
    bool centered_;
  };
}
