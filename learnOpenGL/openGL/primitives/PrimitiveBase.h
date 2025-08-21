#pragma once
#include "../mesh/base/MeshBase.h"
#include "../entity/property/EntityPropertyDimensions.h"

namespace openGL::primitives
{
  class PrimitiveBase
  {
  public:
    PrimitiveBase(const entity::property::EntityPropertyDimensions& dimensions) : dimensions_(dimensions)
    {
    }

    PrimitiveBase() = default;
    virtual ~PrimitiveBase() = default;

  protected:
    virtual mesh::MeshBase generate_primitive_mesh() = 0;
    mesh::MeshBase mesh_;
    std::vector<mesh::base::VertexBase> _vertices;
    std::vector<unsigned int> _indices;

  public:
    [[nodiscard]] mesh::MeshBase& mesh()
    {
      return mesh_;
    }

    void set_mesh(const mesh::MeshBase& mesh)
    {
      mesh_ = mesh;
    }

    __declspec(property(get = mesh, put = set_mesh)) mesh::MeshBase Mesh;

  protected:
    entity::property::EntityPropertyDimensions dimensions_;

    [[nodiscard]] entity::property::EntityPropertyDimensions dimensions() const
    {
      return dimensions_;
    }

    void set_dimensions(const entity::property::EntityPropertyDimensions& dimensions)
    {
      dimensions_ = dimensions;
    }

    __declspec(property(get = dimensions, put = set_dimensions)) entity::property::EntityPropertyDimensions Dimensions;
  };
}
