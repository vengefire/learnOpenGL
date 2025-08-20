#pragma once
#include <vector>

#include "../core/VertexBase.h"

namespace openGL::primitives
{
  class PrimitiveBase
  {
  public:
    PrimitiveBase(float width, float height, float depth)
      : _width(width),
        _height(height),
        _depth(depth)
    {
    }

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
    float _width = 0.0f;
    float _height = 0.0f;
    float _depth = 0.0f;
    std::vector<core::VertexBase> _vertices;

  public:
    [[nodiscard]] float get_width() const
    {
      return _width;
    }

    void set_width(const float width)
    {
      _width = width;
    }

    __declspec(property(get = get_width, put = set_width)) float Width;

    [[nodiscard]] float get_height() const
    {
      return _height;
    }

    void set_height(const float height)
    {
      _height = height;
    }

    __declspec(property(get = get_height, put = set_height)) float Height;

    [[nodiscard]] float get_depth() const
    {
      return _depth;
    }

    void set_depth(const float depth)
    {
      _depth = depth;
    }

    __declspec(property(get = get_depth, put = set_depth)) float Depth;

  protected:
    std::vector<unsigned int> _indices;
  };
}
