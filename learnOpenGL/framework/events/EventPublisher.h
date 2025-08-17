#pragma once
#include <vector>

#include "EventBase.hpp"

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

    void publish_events()
    {
      for (const auto& event : events_)
      {
        if (event)
        {
          event->handle_event();
        }
      }
      events_.clear();
    }
  protected:
    std::vector<std::unique_ptr<EventBase>> events_;
  private:
  };

}
