#pragma once


namespace framework::property
{
  class PropertyHostBase;

  // Base class for property behaviors
  class PropertyBase
  {
  public:
    PropertyBase() = default;

    PropertyBase(const std::shared_ptr<PropertyHostBase>& p_property_host) : _pPropertyHost(p_property_host)
    {
    }

    virtual ~PropertyBase() = default;
  protected:
    std::shared_ptr<PropertyHostBase> _pPropertyHost = nullptr;
  };
}
