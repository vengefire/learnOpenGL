#pragma once
#include "TEventBehaviorBase.h"

#include "../base/TEventBehaviorBase.h"

namespace openGL::framework::behavior::event::property
{

  template <class TEventData>
  class TEventPropertyBehavior :
    public base::TEventBehaviorBase<TEventData>
  {
  };

}