#include "LightModelBase.h"

namespace openGL::lighting
{
  LightModelBase::LightModelBase(
    const mesh::MeshBase& mesh, 
    const std::shared_ptr<shaders::ShaderProgram>& shader,
    const std::shared_ptr<camera::CameraBase>& camera) : ModelBase(mesh, shader, camera)
  {
  }

  LightModelBase::LightModelBase(const model::ModelBase& model) : ModelBase(model)
  {
  }

  LightModelBase::~LightModelBase()
  {
  }

  glm::mat4 LightModelBase::calculate_translation()
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
  }
}
