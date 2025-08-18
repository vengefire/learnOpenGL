#pragma once
#include "EventBase.hpp"

namespace framework::events
{
  template <typename TEventData>
  class TEventBase : public framework::events::EventBase
  {
  public:
    TEventBase(std::string event_name)
      : framework::events::EventBase(std::move(event_name)) {}

    TEventBase(std::string event_name, std::unique_ptr<TEventData> pEvent_data)
      : framework::events::EventBase(std::move(event_name), std::move(pEvent_data)) {}

    ~TEventBase() override = default;

    std::shared_ptr<EventDataBase> get_event_data() const override
    {
      // Downcast the base pointer to the derived type if needed
      return framework::events::EventBase::get_event_data();
    }

    // Optionally, provide a type-safe getter for TEventData
    std::shared_ptr<TEventData> get_typed_event_data() const
    {
      return std::dynamic_pointer_cast<TEventData>(framework::events::EventBase::get_event_data());
    }

    void emit_event(std::shared_ptr<EventDataBase> pEventData) override
    {
      pEvent_data_ = pEventData;
      this->emit_event(get_typed_event_data());
    }

    void emit_event() override
    {
      EventBase::emit_event();
    }

    void emit_event(std::shared_ptr<TEventData> pEvent_data)
    {
      pEvent_data_ = std::move(pEvent_data);
      EventBase::emit_event();
    }
  protected:
  };
}
