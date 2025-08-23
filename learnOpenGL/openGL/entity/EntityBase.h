#pragma once
#include <map>

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
    [[nodiscard]] framework::property::TPropertyBase<int> id() const
    {
      return *std::static_pointer_cast<framework::property::TPropertyBase<int>>(_properties.at("Id"));
    }

    void set_id(const int& id)
    {
      *std::static_pointer_cast<framework::property::TPropertyBase<int>>(_properties.at("Id")) = id;
    }

    __declspec(property(get = id, put = set_id)) framework::property::TPropertyBase<int> Id;

    [[nodiscard]] framework::property::TPropertyBase<std::string> name() const
    {
      return *std::static_pointer_cast<framework::property::TPropertyBase<std::string>>(_properties.at("Name"));
    }

    void set_name(const std::string& name)
    {
      *std::static_pointer_cast<framework::property::TPropertyBase<std::string>>(_properties.at("Name")) = name;
    }

    __declspec(property(get = name, put = set_name)) framework::property::TPropertyBase<std::string> Name;

    [[nodiscard]] framework::property::TPropertyBase<glm::vec3>& position()
    {
      return *std::static_pointer_cast<framework::property::TPropertyBase<glm::vec3>>(_properties.at("Position"));
    }

    void set_position(const framework::property::TPropertyBase<glm::vec3>& position)
    {
      *std::static_pointer_cast<framework::property::TPropertyBase<glm::vec3>>(_properties.at("Position")) = position;
    }

    __declspec(property(get = position, put = set_position)) framework::property::TPropertyBase<glm::vec3>& Position;

    [[nodiscard]] framework::property::TPropertyBase<glm::vec3> orientation() const
    {
      return *std::static_pointer_cast<framework::property::TPropertyBase<glm::vec3>>(_properties.at("Orientation"));
    }

    void set_orientation(const framework::property::TPropertyBase<glm::vec3>& orientation)
    {
      *std::static_pointer_cast<framework::property::TPropertyBase<glm::vec3>>(_properties.at("Orientation")) = orientation;
    }

    __declspec(property(get = orientation, put = set_orientation)) framework::property::TPropertyBase<glm::vec3> Orientation;

    [[nodiscard]] framework::property::TPropertyBase<glm::vec3> scale() const
    {
      return *std::static_pointer_cast<framework::property::TPropertyBase<glm::vec3>>(_properties.at("Scale"));
    }

    void set_scale(const framework::property::TPropertyBase<glm::vec3>& scale)
    {
      *std::static_pointer_cast<framework::property::TPropertyBase<glm::vec3>>(_properties.at("Scale")) = scale;
    }

    __declspec(property(get = scale, put = set_scale)) framework::property::TPropertyBase<glm::vec3> Scale;

  public:
    // Refactor
    void add_behavior(const std::shared_ptr<framework::behavior::base::BehaviorBase> behavior)
    {
      _behaviors.push_back(behavior);
    }

  protected:

    std::map<std::string, std::shared_ptr<framework::property::PropertyBase>> _properties = {
      {"Id", std::make_shared<framework::property::TPropertyBase<int>>(0)},
      {"Name", std::make_shared<framework::property::TPropertyBase<std::string>>("N/A")},
      {"Position", std::make_shared<framework::property::TPropertyBase<glm::vec3>>(glm::vec3(0.0f, 0.0f, 0.0f))},
      {"Orientation", std::make_shared<framework::property::TPropertyBase<glm::vec3>>(glm::vec3(0.0f, 0.0f, 0.0f))},
      {"Scale", std::make_shared<framework::property::TPropertyBase<glm::vec3>>(glm::vec3(1.0f, 1.0f, 1.0f))}
    };

    std::vector<std::shared_ptr<framework::behavior::base::BehaviorBase>> _behaviors{};
  };
}
