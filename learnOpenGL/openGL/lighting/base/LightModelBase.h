#pragma once
#include "LightBase.h"
#include "../../model/ModelBase.h"

namespace openGL::lighting
{
  class LightModelBase :
      public LightBase,
      public model::ModelBase
  {
    public:
    LightModelBase(const mesh::MeshBase& mesh, const std::shared_ptr<shaders::ShaderProgram>& shader, const std::shared_ptr<camera::CameraBase>& camera);
    LightModelBase(const model::ModelBase& model);
    ~LightModelBase() override;

  protected:
    virtual glm::mat4 calculate_translation() override;
  };
}
