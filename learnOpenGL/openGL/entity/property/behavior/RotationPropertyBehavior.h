#pragma once
#include <memory>

#include "../EntityPropertyOrientation.h"
#include "../../../../framework/property/TPropertyBehaviorBase.h"


namespace openGL::entity::property::behavior
{
  class RotationPropertyBehavior : public framework::property::behavior::TPropertyBehaviorBase<EntityPropertyOrientation>
  {
  public:
    RotationPropertyBehavior(const std::shared_ptr<EntityPropertyOrientation>& p_orientation_property)
      : TPropertyBehaviorBase<EntityPropertyOrientation>(glm::vec3 {0.0f, 0.0f, 0.0f}, p_orientation_property)
    {
    }

    RotationPropertyBehavior() = default;
  };
}
