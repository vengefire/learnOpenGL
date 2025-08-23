#pragma once

#include "../../base/BehaviorBase.h"
#include "../../../events/TEventSubscriberBase.h"

namespace openGL::framework::behavior::event::base
{
  template <class TEventData>
  class TEventBehaviorBase :
    public behavior::base::BehaviorBase,
    public framework::events::TEventSubscriberBase<TEventData>
  {
  };
}
