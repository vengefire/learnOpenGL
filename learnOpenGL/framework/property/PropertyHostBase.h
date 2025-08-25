#pragma once
#include <memory>

#include "PropertyBase.h"

namespace framework::property
{
  class PropertyHostBase
  {
  public:
    virtual ~PropertyHostBase() = default;
  protected:
    std::map<std::string, std::shared_ptr<framework::property::PropertyBase>> _properties;
  };
}
