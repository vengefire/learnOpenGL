#pragma once

namespace framework::behavior::base
{
  template <class TBehaviorData>
  class TBehaviorBase
  {
  public:
    virtual void executeBehavior(const TBehaviorData& data) = 0;
  };
}
