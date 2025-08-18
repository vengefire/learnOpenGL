#include "Shader.h"

#include "ShaderProgram.h"

#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/type_ptr.inl>

namespace openGL::shaders
{
  void ShaderProgram::load_shader_from_file(const std::string& shaderSourcePath, GLenum shaderType)
  {
    auto pShader = std::make_unique<Shader>(shaderType);
    pShader->load_from_file(shaderSourcePath, shaderType);
    glAttachShader(this->id_, pShader->get_id());
    attached_shaders_.push_back(std::move(pShader));
  }


  void ShaderProgram::linkProgram()
  {
    glLinkProgram(id_);
    attached_shaders_.clear(); // Clear the attached shaders after linking
    int success;
    char infoLog[512];
    // print linking errors if any
    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(id_, 512, nullptr, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      throw std::runtime_error("ERROR::SHADER::PROGRAM::LINKING_FAILED");
    }
  }

  ShaderProgram::~ShaderProgram()
  {
    if (id_ != 0)
    {
      glDeleteProgram(id_);
      id_ = 0;
    }
    std::cout << "ShaderProgram with ID [" << id_ << "] destroyed.\n";
  }

  ShaderProgram::ShaderProgram(const std::string& name) : name_(name)
  {
    // shader Program
    ShaderProgram::Init();
  }

  void ShaderProgram::use() const
  {
    glUseProgram(id_);
  }

  void ShaderProgram::set_bool(const std::string& name, bool value) const
  {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
  }

  void ShaderProgram::set_int(const std::string& name, int value) const
  {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
  }

  void ShaderProgram::set_float(const std::string& name, float value) const
  {
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
  }

  void ShaderProgram::set_mat4(const std::string& name, glm::mat4 mat4)
  {
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
  }

  void ShaderProgram::Init()
  {
    id_ = glCreateProgram();
    std::cout << std::format("ShaderProgram [{}] with ID [{}] initialized.", name_,id_) << std::endl;
  }
}
