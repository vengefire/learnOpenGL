#pragma once
#include "../../entity/EntityBase.h"

namespace openGL::lighting
{
  class LightBase : public entity::EntityBase
  {
  public:
    LightBase() = default;

    LightBase(const entity::property::EntityPropertyId& id, const entity::property::EntityPropertyName& name,
      const entity::property::EntityPropertyPosition& position,
      const entity::property::EntityPropertyOrientation& orientation,
      const entity::property::EntityPropertyScale& scale)
      : EntityBase(id, name, position, orientation, scale)
    {
    }
  };
}
