#pragma once

#include <memory>

#include "EventDataBase.h"

namespace framework::events
{
  class EventSubscriberBase
  {
  public:
    virtual ~EventSubscriberBase() = default;
    // This method should be overridden by derived classes to handle the event
    virtual void handle_event(std::shared_ptr<EventDataBase> pEventData) = 0;
  };
}
