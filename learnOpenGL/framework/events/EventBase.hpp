#pragma once
#include <memory>
#include <string>

#include "EventDataBase.h"

namespace framework::events
{
  class EventBase
  {
  public:
    EventBase(std::string event_name, std::unique_ptr<framework::events::EventDataBase> pEvent_data) : event_name_(std::move(event_name)), pEvent_data_(std::move(pEvent_data)) {}
    virtual ~EventBase() = default;
    virtual const std::string& get_event_name() const { return event_name_; }
    virtual framework::events::EventDataBase* get_event_data() const { return pEvent_data_.get(); }
    virtual void handle_event() = 0;
  protected:
    std::string event_name_;
    std::unique_ptr<framework::events::EventDataBase> pEvent_data_;
  private:
  };

}
