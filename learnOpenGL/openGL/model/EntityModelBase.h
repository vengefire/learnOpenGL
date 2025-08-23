#pragma once
#include "ModelBase.h"
#include "../entity/EntityBase.h"
#include "../../framework/property/TPropertyBase.h"

namespace openGL::model
{
  class EntityModelBase :
    public ModelBase,
    public entity::EntityBase
  {
  public:
    EntityModelBase(const mesh::MeshBase& mesh, const std::shared_ptr<shaders::ShaderProgram>& shader_program,
                    const std::shared_ptr<camera::CameraBase>& camera)
      : ModelBase(mesh, shader_program, camera)
    {
    }

  protected:
    glm::mat4 calculate_translation() override
    {
      auto trans = glm::mat4(1.0f);
      // Apply Scaling
      trans = glm::scale(trans, Scale->PropertyValue);
      // Apply translation
      trans = glm::translate(trans, Position->PropertyValue);
      // Apply orientation
      trans = glm::rotate(trans, glm::radians(Orientation->PropertyValue.x), glm::vec3(1.0, 0.0, 0.0));
      trans = glm::rotate(trans, glm::radians(Orientation->PropertyValue.y), glm::vec3(0.0, 1.0, 0.0));
      trans = glm::rotate(trans, glm::radians(Orientation->PropertyValue.z), glm::vec3(0.0, 0.0, 1.0));
      return trans;
    };
  };
}
