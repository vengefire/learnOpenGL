#pragma once

#include "../base/TEventBehaviorBase.h"

namespace framework::behavior::event::property
{
  template <class TEventData, class TBehaviorData>
  class TEventPropertyBehavior :
    public framework::behavior::event::base::TEventBehaviorBase<TEventData, TBehaviorData>
  {
  };

}