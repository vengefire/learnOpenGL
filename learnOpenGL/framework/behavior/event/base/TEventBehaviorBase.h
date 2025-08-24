#pragma once

#include <functional>

#include "EventBehaviorBase.h"
#include "../../../events/TEventSubscriberBase.h"
#include "../../base/TBehaviorBase.h"

namespace framework::behavior::event::base
{
  template <class TEventData, class TBehaviorData>
  class TEventBehaviorBase :
    virtual public EventBehaviorBase,
    virtual public events::TEventSubscriberBase<TEventData>
  {
  public:
    TEventBehaviorBase() = default;

    TEventBehaviorBase(const std::shared_ptr<behavior::base::TBehaviorBase<TBehaviorData>>& p_behavior,
                       const std::function<TBehaviorData(const TEventData&)>& event_data_transform_handler)
      : _pBehavior(p_behavior),
        _event_data_transform_handler(event_data_transform_handler)
    {
    }

    void handle_event(std::shared_ptr<events::EventDataBase> pEventData) override
    {
      events::TEventSubscriberBase<TEventData>::handle_event(pEventData);
    }

    void handle_event(std::shared_ptr<TEventData> pEventData) override
    {
      _pBehavior->executeBehavior(std::make_shared<TBehaviorData>(_event_data_transform_handler(*pEventData)));
    }

  protected:
    std::shared_ptr<behavior::base::TBehaviorBase<TBehaviorData>> _pBehavior;
    std::function<TBehaviorData(const TEventData&)> _event_data_transform_handler;
  };
}
