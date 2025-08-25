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
  struct tPropertyBehaviorData : framework::behavior::base::BehaviorDataBase
  {
    tPropertyBehaviorData(const TProperty& value, E_PROPERTY_BEHAVIOR_TYPE behavior_type)
      : type(behavior_type),
        pValue(std::make_shared<TProperty>(value))
    {
    }

    E_PROPERTY_BEHAVIOR_TYPE type; // Type of property behavior
    std::shared_ptr<TProperty> pValue; // Value associated with the behavior
  };

  // Base class for property behaviors
  template <class TProperty>
  class TPropertyBehaviorBase : public framework::behavior::base::TBehaviorBase<tPropertyBehaviorData<TProperty>>
  {
  public:
    TPropertyBehaviorBase(const TProperty& default_value, TProperty* pProperty)
      : _default_value(default_value),
        _pProperty(pProperty)
    {
    }

    TPropertyBehaviorBase() = default;
    // Virtual methods to be overridden by derived classes for specific behaviors

    void executeBehavior(const std::shared_ptr<tPropertyBehaviorData<TProperty>>& pData) override
    {
      switch (pData->type)
      {
      case ePropertyBehaviorTypeAdd:
        applyAddBehavior(*pData->pValue);
        break;
      case ePropertyBehaviorTypeRemove:
        applyRemoveBehavior(*pData->pValue);
        break;
      case ePropertyBehaviorTypeSet:
        applySetBehavior(*pData->pValue);
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

    virtual void applySetBehavior(TProperty& value)
    {
      *_pProperty = value.PropertyValue; // Set the orientation property to the new value
    }

    virtual void applyAddBehavior(TProperty& value)
    {
      *_pProperty += value.PropertyValue; // Add the value to the current orientation property
    }

    virtual void applyRemoveBehavior(TProperty& value)
    {
      *_pProperty -= value.PropertyValue;
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
      *_pProperty = _default_value; // Reset the orientation property to the specified value
    }

  protected:
    TProperty _default_value; // Default value for the orientation property
    TProperty* _pProperty;
  };
}
