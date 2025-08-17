#pragma once

namespace framework::events
{
  class EventDataBase
  {
  public:
    EventDataBase() = default;
    virtual ~EventDataBase() = default;
    // Add any common functionality or properties for event data here
    // For example, you might want to add a timestamp or an event ID
    // std::chrono::system_clock::time_point timestamp;
    // int event_id;
  };
}
