#pragma once
#include "EventBase.hpp"

namespace framework::events
{
  template <typename TEventData>
  class TEventBase : public framework::events::EventBase
  {
    public:
    TEventBase(std::string event_name, std::unique_ptr<TEventData> pEvent_data)
      : framework::events::EventBase(std::move(event_name), std::move(pEvent_data)) {}

    ~TEventBase() override = default;
    TEventData* get_event_data() const override
    {
      // Downcast the base pointer to the derived type
      return static_cast<TEventData*>(framework::events::EventBase::get_event_data());
    }
    void emit_event() override
    {
      EventBase::emit_event();
    }
  protected:
  };
}
