#pragma once

#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec2.hpp>
#include "../../../learnOpenGL/learnOpenGL/framework/property/TPropertyBase.h"

namespace openGL::mesh::base::property
{
  class VertexBasePropertyTexelCoordinates :
    public framework::property::TPropertyBase<glm::vec2>
  {
  public:
    VertexBasePropertyTexelCoordinates() = default;

    VertexBasePropertyTexelCoordinates(const glm::tvec2<float>& property_value)
      : TPropertyBase<glm::tvec2<float>>(property_value)
    {
    }

    float U() { return PropertyValue.x; }
    float V() { return PropertyValue.y; }
  };
}
