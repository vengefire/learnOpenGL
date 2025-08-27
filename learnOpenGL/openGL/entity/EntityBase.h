#pragma once
#include <map>
#include <utility>

#include <glm/glm.hpp>

#include "../../framework/behavior/base/BehaviorBase.h"
#include "../../framework/property/TPropertyHostBase.h"
#include "../entity/property/TEntityPropertyBase.h"

namespace openGL::entity
{
  class EntityBase : public framework::property::TPropertyHostBase<EntityBase>
  {
  public:
    typedef property::TEntityPropertyBase<float> EntityPropertyFloat;
    typedef property::TEntityPropertyBase<glm::vec2> EntityProperty2Vec;
    typedef property::TEntityPropertyBase<glm::vec3> EntityProperty3Vec;
    typedef property::TEntityPropertyBase<glm::vec4> EntityProperty4Vec;
    typedef property::TEntityPropertyBase<int> EntityPropertyInt;
    
    typedef framework::property::TPropertyBase<std::string> PropertyString;
    typedef framework::property::TPropertyBase<float> PropertyFloat;
    typedef framework::property::TPropertyBase<glm::vec3> Property3Vec;
    typedef framework::property::TPropertyBase<glm::vec4> Property4Vec;

  protected:
    EntityBase()
    {
      _properties = {
        { "Id", std::make_shared<EntityPropertyInt>(0)},
        { "Name", std::make_shared<PropertyString>("N/A")},
        { "Position", std::make_shared<EntityProperty3Vec>(glm::vec3(0.0f, 0.0f, 0.0f)) },
        { "Orientation", std::make_shared<EntityProperty3Vec>(glm::vec3(0.0f, 0.0f, 0.0f)) },
        { "Scale", std::make_shared<EntityProperty3Vec>(glm::vec3(1.0f, 1.0f, 1.0f)) }
      };
    }

    virtual void initialize_entity_properties()
    {
    }

    ~EntityBase() override = default;

  public:
    [[nodiscard]] std::shared_ptr<EntityPropertyInt> id() const
    {
      return std::static_pointer_cast<EntityPropertyInt>(_properties.at("Id"));
    }

    void set_id(const int& id)
    {
      *std::static_pointer_cast<EntityPropertyInt>(_properties.at("Id")) = id;
    }

    __declspec(property(get = id)) std::shared_ptr<EntityPropertyInt> Id;

    [[nodiscard]] std::shared_ptr<PropertyString> name() const
    {
      return std::static_pointer_cast<PropertyString>(_properties.at("Name"));
    }

    void set_name(const std::string& name)
    {
      *std::static_pointer_cast<PropertyString>(_properties.at("Name")) = name;
    }

    __declspec(property(get = name)) std::shared_ptr<PropertyString> Name;

    [[nodiscard]] std::shared_ptr<EntityProperty3Vec> position()
    {
      return std::static_pointer_cast<EntityProperty3Vec>(_properties.at("Position"));
    }

    void set_position(const EntityProperty3Vec& position)
    {
      *std::static_pointer_cast<EntityProperty3Vec>(_properties.at("Position")) = position;
    }

    __declspec(property(get = position)) std::shared_ptr<EntityProperty3Vec> Position;

    [[nodiscard]] std::shared_ptr<EntityProperty3Vec> orientation() const
    {
      return std::static_pointer_cast<EntityProperty3Vec>(_properties.at("Orientation"));
    }

    void set_orientation(const EntityProperty3Vec& orientation)
    {
      *std::static_pointer_cast<EntityProperty3Vec>(_properties.at("Orientation")) =
        orientation;
    }

    __declspec(property(get = orientation)) std::shared_ptr<EntityProperty3Vec> Orientation;

    [[nodiscard]] std::shared_ptr<EntityProperty3Vec> scale() const
    {
      return std::static_pointer_cast<EntityProperty3Vec>(_properties.at("Scale"));
    }

    void set_scale(const EntityProperty3Vec& scale)
    {
      *std::static_pointer_cast<EntityProperty3Vec>(_properties.at("Scale")) = scale;
    }

    __declspec(property(get = scale)) std::shared_ptr<EntityProperty3Vec> Scale;
  };
}
