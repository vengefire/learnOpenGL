#pragma once

#include <functional>

#include "../../../events/TEventSubscriberBase.h"
#include "../../base/TBehaviorBase.h"

namespace framework::behavior::event::base
{
  template <class TEventData, class TBehaviorData>
  class TEventBehaviorBase :
    public behavior::base::TBehaviorBase<TBehaviorData>,
    public events::TEventSubscriberBase<TEventData>
  {
  public:
    TEventBehaviorBase(const std::function<TBehaviorData(TEventData)>& event_data_transform_handler) : _event_data_transform_handler(event_data_transform_handler)
    {
    }

  protected:
    std::function<TBehaviorData(TEventData)> _event_data_transform_handler;
  };
}
