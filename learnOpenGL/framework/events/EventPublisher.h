#pragma once
#include <vector>

#include "EventBase.hpp"
#include "TEventSubscriberBase.h"

namespace framework::events
{

  class EventPublisher
  {
  public:
    EventPublisher() = default;
    virtual ~EventPublisher() = default;

    void add_event(std::unique_ptr<EventBase> event)
    {
      events_.emplace_back(std::move(event));
    }

    void emit_event(const type_info& eventType) const
    {
      EventBase* event = get_event_by_type(eventType);
      if (event)
      {
        event->emit_event();
      }
      else
      {
        std::cout << std::format("Event type {} not found\n", eventType.name());
      }
    }

    template <typename TEventDataType> void register_subscriber(TEventSubscriberBase<TEventDataType>* subscriber, const type_info& eventType)
    {
      EventBase* event = get_event_by_type(eventType);
      if (event)
      {
        event->subscribe(subscriber);
      }
      else
      {
        throw std::runtime_error("Event type not found");
      }
    }

    EventBase* get_event_by_type(const type_info& eventType) const
    {
      for (const auto& event : events_)
      {
        if (event && typeid(*event) == eventType)
        {
          return event.get();
        }
      }
      return nullptr;
    }

    void publish_events()
    {
      for (const auto& event : events_)
      {
        if (event)
        {
          event->emit_event();
        }
      }
      events_.clear();
    }
  protected:
    std::vector<std::unique_ptr<EventBase>> events_;
  private:
  };

}
