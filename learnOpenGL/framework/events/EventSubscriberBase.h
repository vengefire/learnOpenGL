#pragma once

#include "EventDataBase.h"

namespace framework::events
{
  class EventSubscriberBase
  {
  public:
    virtual ~EventSubscriberBase() = default;
    // This method should be overridden by derived classes to handle the event
    virtual void handle_event(EventDataBase* pEventData) = 0;
  };
}
