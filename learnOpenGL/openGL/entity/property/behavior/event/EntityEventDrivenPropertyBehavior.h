#pragma once
#include "../../../../../framework/behavior/event/property/TEventPropertyBehavior.h"
#include "../../../../../framework/property/TPropertyBehaviorBase.h"

namespace openGL::entity::property::behavior::event
{
  template <class TEventData, class TProperty>
  class TEntityEventDrivenPropertyBehavior :
    public framework::behavior::event::base::TEventBehaviorBase<TEventData, framework::property::behavior::tPropertyBehaviorData<TProperty>>,
    public framework::property::behavior::TPropertyBehaviorBase<TProperty>
  {
  public:
    TEntityEventDrivenPropertyBehavior(
      const std::function<framework::property::behavior::tPropertyBehaviorData<TProperty>(TEventData)>& event_data_transform_handler, 
      const TProperty& default_value,
      const std::shared_ptr<TProperty>& p_property)
      : framework::behavior::event::base::TEventBehaviorBase<TEventData, framework::property::behavior::tPropertyBehaviorData<TProperty>>(event_data_transform_handler),
        framework::property::behavior::TPropertyBehaviorBase<TProperty>(default_value, p_property)
    {
    }
  };
}
