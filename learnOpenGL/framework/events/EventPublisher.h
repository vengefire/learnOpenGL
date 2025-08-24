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

    auto add_event(std::shared_ptr<EventBase> event)
    {
      events_.emplace_back(std::move(event));
      return events_.back().get();
    }

    void emit_event(const type_info& eventType) const
    {
      if (auto event = get_event_by_type(eventType))
      {
        event->emit_event();
      }
      else
      {
        std::cout << std::format("Event type {} not found\n", eventType.name());
      }
    }

    template <typename TEventDataType> void emit_event(const type_info& eventType, std::shared_ptr<TEventDataType> pEventData) const
    {
      if (auto event = get_event_by_type(eventType))
      {
        event->emit_event(pEventData);
      }
      else
      {
        std::cout << std::format("Event type {} not found\n", eventType.name());
      }
    }

    template <typename TEventDataType> void register_subscriber(TEventSubscriberBase<TEventDataType>* subscriber, const type_info& eventType)
    {
      if (auto event = get_event_by_type(eventType))
      {
        event->register_subscriber(subscriber);
      }
      else
      {
        throw std::runtime_error("Event type not found");
      }
    }

    std::shared_ptr<EventBase> get_event_by_type(const type_info& eventType) const
    {
      for (const auto& event : events_)
      {
        if (event && typeid(*event) == eventType)
        {
          return event;
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
    std::vector<std::shared_ptr<EventBase>> events_;
  private:
  };

}
