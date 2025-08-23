#pragma once
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include "TEntityPropertyBase.h"

namespace openGL::entity::property
{
  class EntityPropertyOrientation : public openGL::entity::property::TEntityPropertyBase<EntityPropertyOrientation, glm::vec3>
  {
  public:
    EntityPropertyOrientation() = default;
    EntityPropertyOrientation(const glm::vec3& orientation)
      : TEntityPropertyBase(orientation)
    {
    }

    float get_x_rotation() const
    {
      return PropertyValue.x;
    }

    void set_x_rotation(float x_rotation)
    {
      property_value_.x = x_rotation;
      mark_property_as_set_and_dirty();
    }

    __declspec(property(get = get_x_rotation, put = get_x_rotation)) float X;

    float get_y_rotation() const
    {
      return PropertyValue.y;
    }

    void set_y_rotation(float y_rotation)
    {
      property_value_.y = y_rotation;
      mark_property_as_set_and_dirty();
    }

    __declspec(property(get = get_y_rotation, put = get_y_rotation)) float Y;

    float get_z_rotation() const
    {
      return PropertyValue.z;
    }

    void set_z_rotation(float z_rotation)
    {
      property_value_.z = z_rotation;
      mark_property_as_set_and_dirty();
    }

    __declspec(property(get = get_z_rotation, put = get_z_rotation)) float Z;
  };
}
