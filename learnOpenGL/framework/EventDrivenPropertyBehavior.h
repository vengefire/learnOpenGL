#pragma once
#include "behavior/event/property/TEventPropertyBehavior.h"
#include "property/TPropertyBehaviorBase.h"

namespace framework
{
  template <class TEventData, class TProperty>
  class TEventDrivenPropertyBehavior :
    public framework::behavior::event::base::TEventBehaviorBase<TEventData, framework::property::behavior::tPropertyBehaviorData<TProperty>>,
    public framework::property::behavior::TPropertyBehaviorBase<TProperty>
  {
  public:
    TEventDrivenPropertyBehavior() :
      framework::behavior::event::base::TEventBehaviorBase<TEventData, framework::property::behavior::tPropertyBehaviorData<TProperty>>(NULL),
      framework::property::behavior::TPropertyBehaviorBase<TProperty>(NULL, NULL)
    {
    }

    TEventDrivenPropertyBehavior(
      std::function<framework::property::behavior::tPropertyBehaviorData<TProperty>(TEventData)> event_data_transform_handler, 
      const TProperty& default_value,
      const std::shared_ptr<TProperty>& p_property)
      : framework::behavior::event::base::TEventBehaviorBase<TEventData, framework::property::behavior::tPropertyBehaviorData<TProperty>>(event_data_transform_handler),
        framework::property::behavior::TPropertyBehaviorBase<TProperty>(default_value, p_property)
    {
    }

    void handle_event(std::shared_ptr<TEventData> pEventData) override
    {
      this->executeBehavior(std::make_shared<framework::property::behavior::tPropertyBehaviorData<TProperty>>(this->_event_data_transform_handler(*pEventData)));
    }

    void executeBehavior(
      const std::shared_ptr<framework::property::behavior::tPropertyBehaviorData<TProperty>>& pData) override
    {
      framework::property::behavior::TPropertyBehaviorBase<TProperty>::executeBehavior(pData);
    }
  };
}
