#pragma once
#include <memory>
#include <string>
#include <vector>

#include "EventDataBase.h"
#include "EventSubscriberBase.h"

namespace framework::events
{
  class EventBase
  {
  public:
    EventBase(std::string event_name, std::unique_ptr<EventDataBase> pEvent_data) : event_name_(std::move(event_name)),
      pEvent_data_(std::move(pEvent_data))
    {
    }

    virtual ~EventBase() = default;
    virtual const std::string& get_event_name() const { return event_name_; }
    virtual EventDataBase* get_event_data() const { return pEvent_data_.get(); }

    virtual void emit_event()
    {
      for (const auto& subscriber : subscribers_)
      {
        subscriber->handle_event(get_event_data());
      }
    }

    virtual void subscribe(EventSubscriberBase* subscriber)
    {
      if (subscriber)
      {
        subscribers_.emplace_back(std::move(subscriber));
      }
    }

  protected:
    std::string event_name_;
    std::unique_ptr<EventDataBase> pEvent_data_;
    std::vector<EventSubscriberBase*> subscribers_;
  };
}
