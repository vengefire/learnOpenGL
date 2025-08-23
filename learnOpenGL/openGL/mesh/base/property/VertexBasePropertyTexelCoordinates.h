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
    float U() const { return PropertyValue.x; }
    float V() const { return PropertyValue.y; }
  };
}
