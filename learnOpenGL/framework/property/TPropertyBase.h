#pragma once
#include <concepts>
#include "PropertyBase.h"

namespace framework::property
{
  template<typename TProperty>
  concept Comparable = std::totally_ordered<TProperty>;

  template <typename TProperty>
  concept Arithmetic = requires(TProperty a, TProperty b) {
    { a + b } -> std::same_as<TProperty>; // Requires that 'a + b' is a valid expression and returns a type convertible to T
  };

  template  <class TProperty>
  class TPropertyBase : public PropertyBase
  {
  public:
    TPropertyBase() = default;

    TPropertyBase(const std::shared_ptr<PropertyHostBase>& p_property_host, const TProperty& property_value)
      : PropertyBase(p_property_host),
        property_value_(property_value)
    {
    }

    TPropertyBase(const TProperty& property_value)
    {
      this->PropertyValue = property_value;
    }

    TPropertyBase(const TProperty& property_value, const std::optional<TProperty>& min_value,
      const std::optional<TProperty>& max_value)
      : property_value_(property_value),
        min_value_(min_value),
        max_value_(max_value)
    {
    }

    TPropertyBase(const TProperty& property_value, const std::optional<TProperty>& default_value)
      : property_value_(property_value),
        default_value_(default_value)
    {
    }

    void checkBounds(TProperty& newValue) requires (Comparable<TProperty>)
    {
      if (max_value_ && newValue > this->max_value_.value())
      {
        std::cout << "Clamping to max value: " << this->max_value_.value() << std::endl;
        newValue = this->max_value_.value();
      }
      else if (min_value_ && newValue < this->min_value_.value())
      {
        std::cout << "Clamping to min value: " << this->min_value_.value() << std::endl;
        newValue = this->min_value_.value();
      }
    }

    void checkBounds(TProperty& newValue) requires (!Comparable<TProperty>)
    {
      return;
    }

    // Allow derived classes to access the property value directly
    TPropertyBase<TProperty>& operator += (const TProperty& rhs)  requires (Arithmetic<TProperty>)
    {
      auto newValue = this->PropertyValue + rhs;
      checkBounds(newValue);
      this->PropertyValue = newValue;

      return *this;
    }

    TPropertyBase<TProperty>& operator -= (const TProperty& rhs)  requires (Arithmetic<TProperty>)
    {
      auto newValue = this->PropertyValue - rhs;
      checkBounds(newValue);
      this->PropertyValue = newValue;
      return *this;
    }

    TPropertyBase<TProperty> operator + (const TProperty& rhs)  requires (Arithmetic<TProperty>)
    {
      this->PropertyValue += rhs;
      return *this;
    }

    TPropertyBase<TProperty> operator - (const TProperty& rhs)  requires (Arithmetic<TProperty>)
    {
      this->PropertyValue -= rhs;
      return *this;
    }

    TPropertyBase<TProperty>& operator = (const TProperty& rhs)
    {
      auto newValue = rhs;
      checkBounds(newValue);
      this->PropertyValue = newValue;
      return *this;
    }

    operator TProperty&()
    {
      return this->PropertyValue;
    }

  protected:
    bool has_value_ = false;
    bool dirty_ = false;
    TProperty property_value_;
    std::optional<TProperty> default_value_;
    std::optional<TProperty> min_value_;
    std::optional<TProperty> max_value_;


  public:
    [[nodiscard]] bool has_value() const
    {
      return has_value_;
    }

    void set_has_value(const bool has_value)
    {
      has_value_ = has_value;
    }

    __declspec(property(get = has_value, put = set_has_value)) bool HasValue;

    [[nodiscard]] bool is_dirty() const
    {
      return dirty_;
    }

    void set_dirty(const bool is_dirty)
    {
      this->dirty_ = is_dirty;
    }

    __declspec(property(get = is_dirty, put = set_dirty)) bool IsDirty;

    [[nodiscard]] TProperty& get_property_value()
    {
      return property_value_;
    }

    void mark_property_as_set_and_dirty()
    {
      this->has_value_ = true; // Mark as having a value when the property value is set
      this->IsDirty = true; // Mark as dirty when the property value is set
    }

    void set_property_value(const TProperty& property_value)
    {
      this->property_value_ = property_value;
      mark_property_as_set_and_dirty();
    }

    __declspec(property(get = get_property_value, put = set_property_value)) TProperty& PropertyValue;
  };

}
