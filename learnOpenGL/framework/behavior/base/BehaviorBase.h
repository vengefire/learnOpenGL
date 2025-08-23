#pragma once

#include <memory>

#include "BehaviorDataBase.h"

namespace framework::behavior::base
{
  // Base class for property behaviors
  class BehaviorBase
  {
  public:
    BehaviorBase() = default;
    virtual ~BehaviorBase() = default;
    // Virtual methods to be overridden by derived classes for specific behaviors
    virtual void executeBehavior(std::shared_ptr<BehaviorDataBase>& pData) = 0;
  };
}
