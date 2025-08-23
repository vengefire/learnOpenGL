#pragma once
#include <map>

#include "../../framework/behavior/base/BehaviorBase.h"
#include "../../framework/property/TPropertyBehaviorBase.h"
#include "property/EntityPropertyId.h"
#include "property/EntityPropertyName.h"
#include "property/EntityPropertyOrientation.h"
#include "property/EntityPropertyPosition.h"
#include "property/EntityPropertyScale.h"

namespace openGL::entity
{
  class EntityBase
  {
  protected:
    EntityBase() = default;
    virtual ~EntityBase() = default;

    EntityBase(const property::EntityPropertyId& id, const property::EntityPropertyName& name,
      const property::EntityPropertyPosition& position, const property::EntityPropertyOrientation& orientation,
      const property::EntityPropertyScale& scale)
      : id_(id),
        name_(name),
        position_(position),
        orientation_(orientation),
        scale_(scale)
    {
      // Constructor initialization list
      // Initialize behaviors_ if needed, or leave it empty
      auto orientationBehaviour = std::make_shared<framework::property::behavior::TPropertyBehaviorBase<property::EntityPropertyOrientation>>(glm::vec3(0.0f), std::make_shared<property::EntityPropertyOrientation>(orientation_));
      add_behavior(orientationBehaviour);
    }

  public:
    [[nodiscard]] property::EntityPropertyId id() const
    {
      return id_;
    }

    void set_id(const property::EntityPropertyId& id)
    {
      id_ = id;
    }

    __declspec(property(get = id, put = set_id)) property::EntityPropertyId Id;

    [[nodiscard]] property::EntityPropertyName name() const
    {
      return name_;
    }

    void set_name(const property::EntityPropertyName& name)
    {
      name_ = name;
    }

    __declspec(property(get = name, put = set_name)) property::EntityPropertyName Name;

    [[nodiscard]] property::EntityPropertyPosition& position()
    {
      return position_;
    }

    void set_position(const property::EntityPropertyPosition& position)
    {
      position_ = position;
    }

    __declspec(property(get = position, put = set_position)) property::EntityPropertyPosition& Position;

    [[nodiscard]] property::EntityPropertyOrientation orientation() const
    {
      return orientation_;
    }

    void set_orientation(const property::EntityPropertyOrientation& orientation)
    {
      orientation_ = orientation;
    }

    __declspec(property(get = orientation, put = set_orientation)) property::EntityPropertyOrientation Orientation;

    [[nodiscard]] property::EntityPropertyScale scale() const
    {
      return scale_;
    }

    void set_scale(const property::EntityPropertyScale& scale)
    {
      scale_ = scale;
    }

    __declspec(property(get = scale, put = set_scale)) property::EntityPropertyScale Scale;

  public:
    // Refactor
    void add_behavior(const std::shared_ptr<framework::behavior::base::BehaviorBase> behavior)
    {
      behaviors_.push_back(behavior);
    }

  protected:
    property::EntityPropertyId id_{0};
    property::EntityPropertyName name_{""};
    property::EntityPropertyPosition position_{glm::vec3(0.0f, 0.0f, 0.0f)};
    property::EntityPropertyOrientation orientation_{glm::vec3(0.0f, 0.0f, 0.0f)};
    property::EntityPropertyScale scale_{glm::vec3(1.0f, 1.0f, 1.0f)};

    std::vector<std::shared_ptr<framework::behavior::base::BehaviorBase>> behaviors_{};
  };
}
