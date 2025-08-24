#pragma once

#include "../../learnOpenGL/framework/property/TPropertyBase.h"
#include "../../learnOpenGL/framework/property/TPropertyBehaviorBase.h"
#include "../../learnOpenGL/framework/events/EventBase.hpp"
#include "../../learnOpenGL/framework/behavior/event/base/EventBehaviorBase.h"
#include "../../learnOpenGL/framework/behavior/event/base/TEventBehaviorBase.h"

namespace openGL::entity::property
{
  template <class TEntityProperty>
  class TEntityPropertyBase :
    public framework::property::TPropertyBase<TEntityProperty>
  {
  public:
    typedef framework::property::TPropertyBase<TEntityProperty> Property;
    typedef framework::property::behavior::TPropertyBehaviorBase<Property> PropertyBehavior;
    typedef framework::events::EventBase Event;
    typedef framework::behavior::event::base::EventBehaviorBase EventBehavior;

    TEntityPropertyBase() : Property()
    {
    }

    TEntityPropertyBase(const TEntityProperty& property_value)
      : Property(property_value),
        _pDefaultPropertyBehavior(std::make_shared<PropertyBehavior>(property_value, this))
    {
    }

    TEntityPropertyBase(const TEntityPropertyBase& other)
      : framework::property::TPropertyBase<TEntityProperty>(other)
    {
    }

    TEntityPropertyBase(TEntityPropertyBase&& other) noexcept
      : framework::property::TPropertyBase<TEntityProperty>(std::move(other))
    {
    }

    TEntityPropertyBase& operator=(const TEntityPropertyBase& other)
    {
      if (this == &other)
        return *this;
      framework::property::TPropertyBase<TEntityProperty>::operator =(other);
      return *this;
    }

    TEntityPropertyBase& operator=(TEntityPropertyBase&& other) noexcept
    {
      if (this == &other)
        return *this;
      framework::property::TPropertyBase<TEntityProperty>::operator =(std::move(other));
      return *this;
    }

    template <class TEventDataType> void AddEventBehavior(std::shared_ptr<Event> pEvent, 
                                                          const std::function<framework::property::behavior::tPropertyBehaviorData<Property>(const TEventDataType&)>& event_data_transform_handler)
    {
      _event_behaviors_.emplace_back(std::make_shared<framework::behavior::event::base::TEventBehaviorBase<TEventDataType, framework::property::behavior::tPropertyBehaviorData<Property>>>(_pDefaultPropertyBehavior, event_data_transform_handler));
      pEvent->register_subscriber(static_cast<framework::behavior::event::base::EventBehaviorBase*>(_event_behaviors_.back().get()));
    }

  protected:
    std::shared_ptr<PropertyBehavior> _pDefaultPropertyBehavior;
    std::vector<std::shared_ptr<EventBehavior>> _event_behaviors_;
  };
}
