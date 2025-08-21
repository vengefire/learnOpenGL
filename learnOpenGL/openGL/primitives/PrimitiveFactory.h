#pragma once

#include "GridPrimitive.h"
#include "PlanePrimitive.h"
#include "CirclePrimitive.h"
#include "CubePrimitive.h"
#include "TrianglePrimitive.h"
#include "UVSpherePrimitive.h"
#include "../entity/property/EntityPropertyDimensions.h"

namespace openGL::primitives
{
  class PrimitiveFactory
  {
  public:
    enum EPrimitiveType
    {
      Triangle,
      Cube
    };

    enum ESegmentedPrimitiveType
    {
      Circle,
      UVSphere,
      GridLines,
      Plane
    };

    static PrimitiveFactory& get_instance()
    {
      static PrimitiveFactory instance;
      return instance;
    }

    static std::shared_ptr<PrimitiveBase> create_primitive(EPrimitiveType primitive_type,
                                                           entity::property::EntityPropertyDimensions dimensions)
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

    static std::shared_ptr<PrimitiveBase> create_segmented_primitive(ESegmentedPrimitiveType primitive_type,
                                                                     entity::property::EntityPropertyDimensions
                                                                     dimensions,
                                                                     entity::property::EntityPropertyDimensions
                                                                     segments)
    {
      switch (primitive_type)
      {
      case Circle:
        {
          auto circle = std::make_shared<CirclePrimitive>(dimensions, segments);
          circle->Generate();
          return circle;
        }
      case UVSphere:
        {
          auto cube = std::make_shared<UVSpherePrimitive>(dimensions, segments);
          cube->Generate();
          return cube;
        }
      case GridLines:
        {
          auto gridLines = std::make_shared<GridPrimitive>(dimensions, segments);
          gridLines->Generate();
          return gridLines;
        }
      case Plane:
        {
          auto plane = std::make_shared<PlanePrimitive>(dimensions, segments);
          plane->Generate();
          return plane;
        }
      default:
        throw std::invalid_argument("Unsupported primitive type");
      }
    }
  };
}
