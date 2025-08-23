#pragma once

#include "BehaviorBase.h"

namespace framework::behavior::base
{
  template <class TBehaviorData>
  class TBehaviorBase : public BehaviorBase
  {
    virtual void executeBehavior(std::shared_ptr<BehaviorDataBase>& pData) override
    {
      this->executeBehavior(reinterpret_cast<std::shared_ptr<TBehaviorData>&>(pData));
    }
    virtual void executeBehavior(const std::shared_ptr<TBehaviorData>& pData) = 0;
  };
}
