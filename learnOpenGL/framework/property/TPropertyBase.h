#pragma once

namespace framework::property
{
  template<class TProperty>
  class TPropertyBase
  {
  public:
    TPropertyBase() = default;
    TPropertyBase(const TProperty& property_value)
    {
      this->PropertyValue = property_value;
    }

  protected:
    bool has_value_ = false;
    bool dirty_ = false;
    TProperty property_value_;

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

    [[nodiscard]] TProperty get_property_value() const
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

    __declspec(property(get = get_property_value, put = set_property_value)) TProperty PropertyValue;
  };

}