#pragma once
#include "Vector3f.h"

namespace openGL::core
{
  class VertexBase
  {
  public:
    // Constructors


    VertexBase(float x, float y, float z) : position_(x, y, z), hasColor_(false), hasTextureCoordinates_(false)
    {
    }

    VertexBase(float x, float y, float z, float r, float g, float b) : position_(x, y, z), hasColor_(false),
                                                                       hasTextureCoordinates_(false)
    {
      VertexBase::set_color(r, g, b);
    }

    VertexBase(float x, float y, float z, float u, float v) : position_(x, y, z), hasColor_(false),
                                                              hasTextureCoordinates_(false)
    {
      VertexBase::set_texture_coordinates(u, v);
    }

    VertexBase(float x, float y, float z, float r, float g, float b, float u, float v) : position_(x, y, z), hasColor_(false), hasTextureCoordinates_(false)
    {
      VertexBase::set_color(r, g, b);
      VertexBase::set_texture_coordinates(u, v);
    }

    virtual ~VertexBase()
    {
    }

    // Setters
    virtual void set_position(float x, float y, float z)
    {
      position_ = Vector3F(x, y, z);
    }

    virtual Vector3F get_position() const
    {
      return position_;
    }

    virtual void set_color(float r, float g, float b)
    {
      color_ = Vector3F(r, g, b);
      hasColor_ = true;
    }

    virtual Vector3F get_color() const
    {
      return color_;
    }

    virtual void set_texture_coordinates(float u, float v)
    {
      texture_coordinates_ = Vector3F(u, v, 0.0f);
      hasTextureCoordinates_ = true;
    }

    virtual Vector3F get_texture_coordinates() const
    {
      return texture_coordinates_;
    }

    // Getters
    virtual float get_position_x() const { return position_.first(); }
    virtual float get_position_y() const { return position_.second(); }
    virtual float get_position_z() const { return position_.third(); }

    virtual float get_color_r() const { return color_.first(); }
    virtual float get_color_g() const { return color_.second(); }
    virtual float get_color_b() const { return color_.third(); }

    virtual float get_texture_coordinate_u() const { return texture_coordinates_.first(); }
    virtual float get_texture_coordinate_v() const { return texture_coordinates_.second(); }

    bool hasTextureCoordinates();
    bool hasColor();

  protected:
    Vector3F position_{0.0f, 0.0f, 0.0f};
    bool hasColor_ = false;
    Vector3F color_{1.0f, 1.0f, 1.0f}; // Default color is white
    bool hasTextureCoordinates_ = false;
    Vector3F texture_coordinates_{0.0f, 0.0f, 0.0f}; // Default texture coordinates
  };

  inline bool VertexBase::hasTextureCoordinates()
  {
    return hasTextureCoordinates_;
  }

  inline bool VertexBase::hasColor()
  {
    return hasColor_;
  }
}
