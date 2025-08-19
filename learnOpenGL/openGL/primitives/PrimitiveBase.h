#pragma once
#include <vector>

#include "../core/VertexBase.h"

namespace openGL::primitives
{
  class PrimitiveBase
  {
  public:
    virtual ~PrimitiveBase() = default;

    virtual std::vector<core::VertexBase> get_vertices() const
    {
      return _vertices;
    }

    virtual std::vector<unsigned int> get_indices() const
    {
      return _indices;
    }

    virtual void generate_primitive() = 0;
  protected:
    std::vector<core::VertexBase> _vertices;
    std::vector<unsigned int> _indices;
  };
}
