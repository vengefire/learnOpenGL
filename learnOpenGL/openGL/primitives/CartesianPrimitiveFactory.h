#pragma once

#include "CubePrimitive.h"
#include "TrianglePrimitive.h"
#include "../entity/property/EntityPropertyDimensions.h"

namespace openGL::primitives
{
  class CartesianPrimitiveFactory
  {
  public:
    enum ECartesianPrimitiveType
    {
      Triangle,
      Cube
    };

    static CartesianPrimitiveFactory& get_instance()
    {
      static CartesianPrimitiveFactory instance;
      return instance;
    }

    static std::shared_ptr<PrimitiveBase> create_primitive(ECartesianPrimitiveType primitive_type, entity::property::EntityPropertyDimensions dimensions)
    {
      switch (primitive_type)
      {
      case Triangle:
        {
          auto triangle = std::make_shared<TrianglePrimitive>(dimensions);
          triangle->Generate();
          return triangle;
      }
      case Cube:
        {
          auto cube = std::make_shared<CubePrimitive>(dimensions);
          cube->Generate();
          return cube;
        }
      default:
        throw std::invalid_argument("Unsupported primitive type");
      }
    }
  };
}
