#pragma once
#include <memory>

#include "../behavior/base/TBehaviorBase.h"

namespace framework::property::behavior
{
  enum E_PROPERTY_BEHAVIOR_TYPE
  {
    ePropertyBehaviorTypeSet,
    ePropertyBehaviorTypeAdd,
    ePropertyBehaviorTypeRemove,
    // ePropertyBehaviorTypeProduct,
    // ePropertyBehaviorTypeDivision,
    ePropertyBehaviorTypeReset
  };

  template <class TProperty>
  struct tPropertyBehaviorData
  {
    E_PROPERTY_BEHAVIOR_TYPE type; // Type of property behavior
    std::shared_ptr<TProperty> pValue;               // Value associated with the behavior
  };

  // Base class for property behaviors
  template <class TProperty>
  class TPropertyBehaviorBase : public framework::behavior::base::TBehaviorBase<tPropertyBehaviorData<TProperty>>
  {
  public:
    TPropertyBehaviorBase(const TProperty& default_value, const std::shared_ptr<TProperty>& p_orientation_property)
      : _default_value(default_value),
        _pOrientation_property(p_orientation_property)
    {
    }

    TPropertyBehaviorBase() = default;
    virtual ~TPropertyBehaviorBase() = default;
    // Virtual methods to be overridden by derived classes for specific behaviors

    void executeBehavior(const tPropertyBehaviorData<TProperty>& data) override
    {
      switch (data.type)
      {
      case ePropertyBehaviorTypeAdd:
        applyAddBehavior(*data.pValue);
        break;
      case ePropertyBehaviorTypeRemove:
        applyRemoveBehavior(*data.pValue);
        break;
      case ePropertyBehaviorTypeSet:
        applySetBehavior(*data.pValue);
        break;
        // case ePropertyBehaviorTypeProduct:
        //   applyProductBehavior(*data.pValue);
        //   break;
        // case ePropertyBehaviorTypeDivision:
        //   applyDivisionBehavior(*data.pValue);
        //   break;
      case ePropertyBehaviorTypeReset:
        applyResetBehavior();
        break;
      }
    }

    virtual void applySetBehavior(const TProperty& value)
    {
      _pOrientation_property->PropertyValue = value.PropertyValue; // Set the orientation property to the new value
    }

    virtual void applyAddBehavior(const TProperty& value)
    {
      _pOrientation_property->PropertyValue += value.PropertyValue; // Add the value to the current orientation property
    }

    virtual void applyRemoveBehavior(const TProperty& value)
    {
      _pOrientation_property->PropertyValue -= value.PropertyValue;
    }

    /*virtual void applyProductBehavior(const EntityPropertyOrientation& value)
    {
      _pOrientation_property->PropertyValue *= value.PropertyValue; // Remove the value from the current orientation property
    }
    virtual void applyDivisionBehavior(const EntityPropertyOrientation& value)
    {
      _pOrientation_property->PropertyValue /= value.PropertyValue; // Remove the value from the current orientation property
    }*/
    virtual void applyResetBehavior()
    {
      *_pOrientation_property = _default_value; // Reset the orientation property to the specified value
    }

  protected:
    TProperty _default_value; // Default value for the orientation property
    std::shared_ptr<TProperty> _pOrientation_property;
  };
}
