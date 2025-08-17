#pragma once

#include "../../config.h"

namespace openGL::shaders
{
  class Shader
  {
  public:
    Shader(GLenum shader_Type);
    virtual ~Shader();
    void load_from_file(std::string shaderSourcePath, GLenum shaderType) const;

    int get_id() const
    {
      return id_;
    }

  protected:
    void Init();

  private:
    unsigned int id_ = -1;
    GLenum shader_type_;
  };
}
