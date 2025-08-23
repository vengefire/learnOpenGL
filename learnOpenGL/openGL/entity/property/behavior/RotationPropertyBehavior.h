#pragma once
#include <memory>

#include "../EntityPropertyOrientation.h"


namespace openGL::entity::property::behavior
{
  class RotationPropertyBehavior
  {
  public:
    RotationPropertyBehavior(const std::shared_ptr<EntityPropertyOrientation>& orientation_property)
      : _pOrientation_property(orientation_property)
    {
    }

    RotationPropertyBehavior() = default;
    virtual ~RotationPropertyBehavior() = default;
    virtual void applySetBehavior(const EntityPropertyOrientation& value)
    {
      *_pOrientation_property = value; // Set the orientation property to the new value
    }
    virtual void applyAddBehavior(const EntityPropertyOrientation& value)
    {
      *_pOrientation_property += value; // Add the value to the current orientation property
    }
    virtual void applyRemoveBehavior(const EntityPropertyOrientation& value)
    {
      *_pOrientation_property -= value; // Remove the value from the current orientation property
    }
    virtual void applyResetBehavior()
    {
      *_pOrientation_property = value; // Reset the orientation property to the specified value
    }
    // Override the handle_event method to implement rotation behavior
  protected:
    EntityPropertyOrientation _default_value; // Default value for the orientation property
    std::shared_ptr<EntityPropertyOrientation> _pOrientation_property;
  };
}
