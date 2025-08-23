#pragma once
#include "behavior/event/property/TEventPropertyBehavior.h"
#include "property/TPropertyBehaviorBase.h"

namespace framework
{
  template <class TEventData, class TProperty>
  class TEventPropertyBehavior :
    public framework::behavior::event::base::TEventBehaviorBase<TEventData, framework::property::behavior::tPropertyBehaviorData<TProperty>>,
    public framework::property::behavior::TPropertyBehaviorBase<TProperty>
  {
  public:
    TEventPropertyBehavior(
      const std::shared_ptr<behavior::base::TBehaviorBase<property::behavior::tPropertyBehaviorData<TProperty>>>& p_behavior,
      const std::function<property::behavior::tPropertyBehaviorData<TProperty>(const TEventData&)>& event_data_transform_handler, 
      const TProperty& default_value, 
      const std::shared_ptr<TProperty>& pProperty)
      : behavior::event::base::TEventBehaviorBase<TEventData, property::behavior::tPropertyBehaviorData<TProperty>>(p_behavior, event_data_transform_handler),
        property::behavior::TPropertyBehaviorBase<TProperty>(default_value, pProperty)
    {
    }

    void executeBehavior(
      const std::shared_ptr<framework::property::behavior::tPropertyBehaviorData<TProperty>>& pData) override
    {
      framework::property::behavior::TPropertyBehaviorBase<TProperty>::executeBehavior(pData);
    }
  };
}
