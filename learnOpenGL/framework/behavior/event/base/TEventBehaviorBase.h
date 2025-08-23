#pragma once

#include <functional>

#include "../../../../EventBehaviorBase.h"
#include "../../../events/TEventSubscriberBase.h"
#include "../../base/TBehaviorBase.h"

namespace framework::behavior::event::base
{
  template <class TEventData, class TBehaviorData>
  class TEventBehaviorBase :
    public EventBehaviorBase,
    public behavior::base::TBehaviorBase<TBehaviorData>,
    public events::TEventSubscriberBase<TEventData>
  {
  public:
    TEventBehaviorBase(std::function<TBehaviorData(const TEventData&)> event_data_transform_handler) : _event_data_transform_handler(event_data_transform_handler)
    {
    }

  protected:
    std::function<TBehaviorData(const  TEventData&)> _event_data_transform_handler;
  };
}
