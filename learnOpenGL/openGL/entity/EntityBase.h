#pragma once
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
    }

  protected:
    property::EntityPropertyId id_{0};
    property::EntityPropertyName name_{""};
    property::EntityPropertyPosition position_{glm::vec3(0.0f, 0.0f, 0.0f)};
    property::EntityPropertyOrientation orientation_{glm::vec3(0.0f, 0.0f, 0.0f)};
    property::EntityPropertyScale scale_{glm::vec3(1.0f, 1.0f, 1.0f)};
  };
}
