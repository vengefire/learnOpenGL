#pragma once
#include "../../entity/EntityBase.h"

namespace openGL::lighting
{
  class LightBase : public entity::EntityBase
  {
  public:
    LightBase() = default;
    ~LightBase() override = default;
  };
}
