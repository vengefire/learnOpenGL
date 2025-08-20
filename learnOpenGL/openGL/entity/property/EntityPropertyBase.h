#pragma once

namespace openGl::entity::property
{
  template<class TEntityProperty>
  class EntityPropertyBase
  {
  public:
    EntityPropertyBase(const TEntityProperty& property_value)
      : property_value(property_value)
    {
    }

  protected:
    bool is_dirty = false;
    TEntityProperty property_value;

  public:
    [[nodiscard]] bool is_is_dirty() const
    {
      return is_dirty;
    }

    void set_is_dirty(const bool is_dirty)
    {
      this->is_dirty = is_dirty;
    }

    __declspec(property(get = is_is_dirty, put = set_is_dirty)) bool IsDirty;

    [[nodiscard]] TEntityProperty get_property_value() const
    {
      return property_value;
    }

    void set_property_value(const TEntityProperty& property_value)
    {
      this->property_value = property_value;
      this->is_dirty = true; // Mark as dirty when the property value is set
    }

    __declspec(property(get = get_property_value, put = set_property_value)) TEntityProperty PropertyValue;
  };

}