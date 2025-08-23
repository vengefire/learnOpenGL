#pragma once
#include <functional>

namespace openGL::framework::behavior::event::property
{
  template <class TEventData>
  class TRotationPropertyEventBehavior :
    public base::TEventBehaviorBase<TEventData>
  {
  public:
    TRotationPropertyEventBehavior() = default;
    virtual ~TRotationPropertyEventBehavior() = default;
    // Override the handle_event method to implement rotation behavior
    void handle_event(std::shared_ptr<TEventData> pEventData) override
    {
      // Implement rotation logic here
      // For example, update rotation properties based on event data
    }
  protected:
    std::function<(TEventData eventData)> onRotation = nullptr;
  };
}
