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
    virtual void handle_event(TEventData* pEventData) = 0;
    virtual void handle_event(EventDataBase* pEventData)
    {
      this->handle_event(static_cast<TEventData*>(pEventData));
    }
  };
}
