#pragma once
#include "EventSubscriberBase.h"

namespace framework::events
{
  template <class TEventData>
  class TEventSubscriberBase : public EventSubscriberBase
  {
    public:
    virtual ~TEventSubscriberBase() = default;
    // This method should be overridden by derived classes to handle the event
    virtual void handle_event(std::shared_ptr<TEventData> pEventData) = 0;

    virtual void handle_event(std::shared_ptr<EventDataBase> pEventData)
    {
      this->handle_event(std::reinterpret_pointer_cast<TEventData>(pEventData));
    }
  };
}
