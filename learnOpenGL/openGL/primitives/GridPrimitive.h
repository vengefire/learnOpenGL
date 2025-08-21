#pragma once
#include "SegmentedTypedPrimitiveBase.h"
#include "TypedPrimitiveBase.h"

namespace openGL::primitives
{
  class GridPrimitive : public SegmentedTypedPrimitiveBase<GridPrimitive>
  {
  public:
    GridPrimitive(const entity::property::EntityPropertyDimensions& dimensions,
                  const entity::property::EntityPropertyDimensions& segments)
      : SegmentedTypedPrimitiveBase<GridPrimitive>(dimensions, segments)
    {
      centered_ = true;
    }

    GridPrimitive(entity::property::EntityPropertyDimensions dimensions, float grid_line_spacing)
      : GridPrimitive(dimensions, glm::vec3(grid_line_spacing, grid_line_spacing, grid_line_spacing))
    {
    }

    static GridPrimitive generate_grid(float width, float height, float depth, float grid_line_spacing, bool centered)
    {
      auto gridPrimitive = GridPrimitive(glm::vec3{width, height, depth}, grid_line_spacing);
      gridPrimitive = generate_primitive(gridPrimitive);
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

      float x_line_spacing = Segments.Width;
      float y_line_spacing = Segments.Height;
      float z_line_spacing = Segments.Depth;

      float width_excess = !centered_ ? 0.0f : fmod(halfWidth, x_line_spacing);
      float height_excess = !centered_ ? 0.0f : fmod(halfHeight, y_line_spacing);
      float depth_excess = !centered_ ? 0.0f : fmod(halfDepth, z_line_spacing);

      auto start = glm::vec3(-halfWidth + width_excess, -halfHeight + height_excess, -halfDepth + depth_excess);
      auto end = glm::vec3(halfWidth - width_excess, halfHeight - height_excess, halfDepth - depth_excess);

      for (float z = start.z; z <= halfDepth; z += z_line_spacing)
      {
        for (float x = start.x; x <= halfWidth; x += x_line_spacing)
        {
          _vertices.emplace_back(x, -halfHeight, z);
          _vertices.emplace_back(x, halfHeight, z);
        }

        for (float y = start.y; y <= halfHeight; y += y_line_spacing)
        {
          _vertices.emplace_back(-halfWidth, y, z);
          _vertices.emplace_back(halfWidth, y, z);
        }
      }

      for (float x = start.x; x <= halfWidth; x += x_line_spacing)
      {
        for (float y = start.y; y <= halfHeight; y += y_line_spacing)
        {
          _vertices.emplace_back(x, y, -halfDepth);
          _vertices.emplace_back(x, y, halfDepth);
        }
      }

      auto mesh = mesh::MeshBase{ _vertices, _indices };
      mesh.DrawLines = true;
      return mesh;
    }

  private:
    bool centered_;
  };
}
