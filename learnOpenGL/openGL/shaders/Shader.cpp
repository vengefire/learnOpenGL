#include "Shader.h"

namespace openGL::shaders
{
  Shader::Shader(GLenum shader_Type) : shader_type_(shader_Type)
  {
    Init();
  }

  void Shader::load_from_file(const std::string shaderSourcePath, GLenum shaderType) const
  {
    std::cout << "Current working directory is [" << std::filesystem::current_path() << "]\n";
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string shaderSource;
    try
    {
      shaderFile.open(shaderSourcePath);
      std::stringstream shaderStream;
      shaderStream << shaderFile.rdbuf();
      shaderFile.close();
      shaderSource = shaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
      std::cout << "ERROR::SHADER::FILE_READ_FAIL - " << shaderSourcePath << " - " << e.what() << "\n";
      throw;
    }

    const char* shaderSourceCStr = shaderSource.c_str();
    glShaderSource(id_, 1, &shaderSourceCStr, nullptr);
    glCompileShader(id_);
    int success;
    char infoLog[512];
    glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(id_, 512, nullptr, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      throw std::runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
    }
  }

  Shader::~Shader()
  {
    glDeleteShader(this->id_);
    std::cout << "Shader with ID [" << id_ << "] destroyed.\n";
  }

  void Shader::Init()
  {
    id_ = glCreateShader(shader_type_);
    std::cout << "Shader with ID [" << id_ << "] initialized.\n";
  }
}
