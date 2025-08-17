#pragma once
#include "openGL/core/Vector3f.h"

namespace openGL::vertex
{
  class VertexBase
  {
  public:
    VertexBase() = default;
    VertexBase(float x, float y, float z) : position_(x, y, z), has_color_(false), has_texture_coordinates_(false) {}
    VertexBase(float x, float y, float z, float r, float g, float b)
      : position_(x, y, z), has_color_(true), color_(r, g, b), has_texture_coordinates_(false) {
    }
    VertexBase(float x, float y, float z, float u, float v)
      : position_(x, y, z), has_color_(false), has_texture_coordinates_(true), texture_coordinates_(u, v, 0.0f) {
    }
    virtual ~VertexBase() = default;

    // Setters
    virtual void set_position(float x, float y, float z) { position_ = core::Vector3F(x, y, z); }
    virtual void set_color(float r, float g, float b) { color_ = core::Vector3F(r, g, b); }
    virtual void set_texture_coordinates(float u, float v) { texture_coordinates_ = core::Vector3F(u, v, 0.0f); }

    // Getters
    virtual float get_position_x() const { return position_.first(); }
    virtual float get_position_y() const { return position_.second(); }
    virtual float get_position_z() const { return position_.third(); }

    virtual float get_color_r() const { return color_.first(); }
    virtual float get_color_g() const { return color_.second(); }
    virtual float get_color_b() const { return color_.third(); }

    virtual float get_texture_coordinate_u() const { return texture_coordinates_.first(); }
    virtual float get_texture_coordinate_v() const { return texture_coordinates_.second(); }

  protected:
    core::Vector3F position_{ 0.0f, 0.0f, 0.0f };
    bool has_color_ = false;
    core::Vector3F color_{ 1.0f, 1.0f, 1.0f }; // Default color is white
    bool has_texture_coordinates_ = false;
    core::Vector3F texture_coordinates_{ 0.0f, 0.0f, 0.0f }; // Default texture coordinates
  };
}