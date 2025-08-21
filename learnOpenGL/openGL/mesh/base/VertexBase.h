#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/detail/type_vec4.hpp>

#include "../../entity/property/EntityPropertyColor.h"
#include "../../entity/property/EntityPropertyNormal.h"
#include "../../entity/property/EntityPropertyPosition.h"
#include "property/VertexBasePropertyTexelCoordinates.h"

namespace openGL::mesh::base
{
  class VertexBase
  {
  public:
    VertexBase(const entity::property::EntityPropertyPosition& position)
      : position_(position)
    {
    }

    VertexBase(const float& x, const float& y, const float& z)
      : position_(glm::vec3(x, y, z))
    {
    }

    VertexBase(const float& x, const float& y, const float& z, const float& u, const float& v)
      : position_(glm::vec3(x, y, z)),
        texture_coordinates_(glm::vec2(u, v))
    {
    }

    VertexBase(const float& x, const float& y, const float& z, const float& u, const float& v, const float& nx, const float& ny, const float& nz)
      : position_(glm::vec3(x, y, z)),
        texture_coordinates_(glm::vec2(u, v)),
        normal_(glm::vec3(nx, ny, nz))
    {
    }

    VertexBase(const entity::property::EntityPropertyPosition& position,
      const entity::property::EntityPropertyColor& color)
      : position_(position),
        color_(color)
    {
    }

    VertexBase(const entity::property::EntityPropertyPosition& position,
      const entity::property::EntityPropertyColor& color,
      const property::VertexBasePropertyTexelCoordinates& texture_coordinates)
      : position_(position),
        color_(color),
        texture_coordinates_(texture_coordinates)
    {
    }

    VertexBase(const entity::property::EntityPropertyPosition& position,
      const property::VertexBasePropertyTexelCoordinates& texture_coordinates)
      : position_(position),
        texture_coordinates_(texture_coordinates)
    {
    }

  protected:
    entity::property::EntityPropertyPosition position_ = glm::vec3{ 0.0f, 0.0f , 0.0f };
    entity::property::EntityPropertyNormal normal_;
    entity::property::EntityPropertyColor color_;
    property::VertexBasePropertyTexelCoordinates texture_coordinates_;

  public:
    [[nodiscard]] entity::property::EntityPropertyPosition get_position() const
    {
      return position_;
    }

    void set_position(const entity::property::EntityPropertyPosition& position)
    {
      position_ = position;
    }

    __declspec(property(get = get_position, put = set_position)) entity::property::EntityPropertyPosition Position;

    [[nodiscard]] entity::property::EntityPropertyNormal get_normal() const
    {
      return normal_;
    }

    void set_normal(const entity::property::EntityPropertyNormal& normal)
    {
      normal_ = normal;
    }

    __declspec(property(get = get_normal, put = set_normal)) entity::property::EntityPropertyNormal Normal;

    [[nodiscard]] entity::property::EntityPropertyColor get_color() const
    {
      return color_;
    }

    void set_color(const entity::property::EntityPropertyColor& color)
    {
      color_ = color;
    }

    __declspec(property(get = get_color, put = set_color)) entity::property::EntityPropertyColor Color;

    [[nodiscard]] property::VertexBasePropertyTexelCoordinates get_texture_coordinates() const
    {
      return texture_coordinates_;
    }

    void set_texture_coordinates(const property::VertexBasePropertyTexelCoordinates& texture_coordinates)
    {
      texture_coordinates_ = texture_coordinates;
    }

    __declspec(property(get = get_texture_coordinates, put = set_texture_coordinates)) property::
    VertexBasePropertyTexelCoordinates TextureCoordinates;
  };
}
