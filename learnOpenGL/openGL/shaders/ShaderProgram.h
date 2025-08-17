#pragma once

#include "../../config.h"
#include "Shader.h"

namespace openGL::shaders
{
  class ShaderProgram
  {
  public:
    virtual ~ShaderProgram();
    ShaderProgram();
    void load_shader_from_file(const std::string& shaderSourcePath, GLenum shaderType);
    void linkProgram();
    void use() const;
    void set_bool(const std::string& name, bool value) const;
    void set_int(const std::string& name, int value) const;
    void set_float(const std::string& name, float value) const;

    unsigned int get_id() const
    {
      return id_;
    };

  protected:
    virtual void Init();
    std::vector<std::unique_ptr<Shader>> attached_shaders_;

  private:
    unsigned int id_ = 0;
  };
}
