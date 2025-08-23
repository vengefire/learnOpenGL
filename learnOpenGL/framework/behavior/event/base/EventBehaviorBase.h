#pragma once
#include "../../../events/EventSubscriberBase.h"

namespace framework::behavior::event::base
{
  class EventBehaviorBase : public events::EventSubscriberBase
  {
  public:
    EventBehaviorBase() = default;
    virtual ~EventBehaviorBase() = default;
  };

}
