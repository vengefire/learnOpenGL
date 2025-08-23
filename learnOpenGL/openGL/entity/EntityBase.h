#pragma once
#include <map>
#include <utility>

#include "../../framework/behavior/base/BehaviorBase.h"
#include "../../framework/property/TPropertyBehaviorBase.h"

namespace openGL::entity
{
  class EntityBase
  {
  protected:
    EntityBase()
    {
      // auto orientationBehaviour = std::make_shared<framework::property::behavior::TPropertyBehaviorBase<property::EntityPropertyOrientation>>(glm::vec3(0.0f), std::make_shared<property::EntityPropertyOrientation>(orientation_));
    };

    virtual ~EntityBase() = default;

  public:
    [[nodiscard]] std::shared_ptr<framework::property::TPropertyBase<int>> id() const
    {
      return std::static_pointer_cast<framework::property::TPropertyBase<int>>(_properties.at("Id"));
    }

    void set_id(const int& id)
    {
      *std::static_pointer_cast<framework::property::TPropertyBase<int>>(_properties.at("Id")) = id;
    }

    __declspec(property(get = id)) std::shared_ptr<framework::property::TPropertyBase<int>> Id;

    [[nodiscard]] std::shared_ptr<framework::property::TPropertyBase<std::string>> name() const
    {
      return std::static_pointer_cast<framework::property::TPropertyBase<std::string>>(_properties.at("Name"));
    }

    void set_name(const std::string& name)
    {
      *std::static_pointer_cast<framework::property::TPropertyBase<std::string>>(_properties.at("Name")) = name;
    }

    __declspec(property(get = name)) std::shared_ptr<framework::property::TPropertyBase<std::string>> Name;

    [[nodiscard]] std::shared_ptr<framework::property::TPropertyBase<glm::vec3>> position()
    {
      return std::static_pointer_cast<framework::property::TPropertyBase<glm::vec3>>(_properties.at("Position"));
    }

    void set_position(const framework::property::TPropertyBase<glm::vec3>& position)
    {
      *std::static_pointer_cast<framework::property::TPropertyBase<glm::vec3>>(_properties.at("Position")) = position;
    }

    __declspec(property(get = position)) std::shared_ptr<framework::property::TPropertyBase<glm::vec3>> Position;

    [[nodiscard]] std::shared_ptr<framework::property::TPropertyBase<glm::vec3>> orientation() const
    {
      return std::static_pointer_cast<framework::property::TPropertyBase<glm::vec3>>(_properties.at("Orientation"));
    }

    void set_orientation(const framework::property::TPropertyBase<glm::vec3>& orientation)
    {
      *std::static_pointer_cast<framework::property::TPropertyBase<glm::vec3>>(_properties.at("Orientation")) =
        orientation;
    }

    __declspec(property(get = orientation)) std::shared_ptr<framework::property::TPropertyBase<glm::vec3>> Orientation;

    [[nodiscard]] std::shared_ptr<framework::property::TPropertyBase<glm::vec3>> scale() const
    {
      return std::static_pointer_cast<framework::property::TPropertyBase<glm::vec3>>(_properties.at("Scale"));
    }

    void set_scale(const framework::property::TPropertyBase<glm::vec3>& scale)
    {
      *std::static_pointer_cast<framework::property::TPropertyBase<glm::vec3>>(_properties.at("Scale")) = scale;
    }

    __declspec(property(get = scale)) std::shared_ptr<framework::property::TPropertyBase<glm::vec3>> Scale;

    // Refactor to use a more generic method to add properties
    std::pair<std::shared_ptr<framework::property::PropertyBase>, std::shared_ptr<
                framework::behavior::base::BehaviorBase>> add_property_behavior(
      std::shared_ptr<framework::property::PropertyBase> property, std::string behavior_name,
      std::shared_ptr<framework::behavior::base::BehaviorBase> behavior)
    {
      if (!_propertyBehaviors.contains(property))
      {
        _propertyBehaviors[property] = std::map<std::string, std::shared_ptr<
                                                  framework::behavior::base::BehaviorBase>>();
      }
      _propertyBehaviors[property][behavior_name] = std::move(behavior);
      return {property, behavior};
    }

    void add_behavior_event(std::shared_ptr<framework::behavior::base::BehaviorBase> behavior, framework::behavior::event::base::EventBehaviorBase eventBehavior)
    {
      _eventBehaviors.push_back(std::move(eventBehavior));
    }

  protected:
    std::map<std::string, std::shared_ptr<framework::property::PropertyBase>> _properties = {
      {"Id", std::make_shared<framework::property::TPropertyBase<int>>(0)},
      {"Name", std::make_shared<framework::property::TPropertyBase<std::string>>("N/A")},
      {"Position", std::make_shared<framework::property::TPropertyBase<glm::vec3>>(glm::vec3(0.0f, 0.0f, 0.0f))},
      {"Orientation", std::make_shared<framework::property::TPropertyBase<glm::vec3>>(glm::vec3(0.0f, 0.0f, 0.0f))},
      {"Scale", std::make_shared<framework::property::TPropertyBase<glm::vec3>>(glm::vec3(1.0f, 1.0f, 1.0f))}
    };

    std::map<std::shared_ptr<framework::property::PropertyBase>, std::map<std::string, std::shared_ptr<framework::behavior::base::BehaviorBase>>> _propertyBehaviors;
    std::vector<framework::behavior::event::base::EventBehaviorBase> _eventBehaviors;
  };
}
