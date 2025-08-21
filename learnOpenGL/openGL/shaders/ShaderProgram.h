#pragma once

#include <functional>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_vec.hpp>

#include "../../config.h"
#include "Shader.h"

namespace openGL::shaders
{
  class ShaderProgram
  {
  public:
    ShaderProgram(const std::string& name);
    virtual ~ShaderProgram();
    void load_shader_from_file(const std::string& shaderSourcePath, GLenum shaderType);
    void linkProgram();
    void use() const;
    void set_bool(const std::string& name, bool value) const;
    void set_int(const std::string& name, int value) const;
    void set_float(const std::string& name, float value) const;
    void set_mat4(const std::string&, glm::mat4 mat4);

    unsigned int get_id() const
    {
      return id_;
    }

    void set_vec4(const std::string& name, const glm::vec4& color);

  protected:
    virtual void Init();
    std::vector<std::unique_ptr<Shader>> attached_shaders_;
    std::function<void(std::shared_ptr<ShaderProgram>)> onRender = nullptr;

  public:
    [[nodiscard]] std::function<void(std::shared_ptr<ShaderProgram>)> on_render() const
    {
      return onRender;
    }

    void set_on_render(const std::function<void(std::shared_ptr<ShaderProgram>)>& on_render)
    {
      onRender = on_render;
    }

    __declspec(property(get = on_render, put = set_on_render)) std::function<void(std::shared_ptr<ShaderProgram>)>
    OnRender;

  private:
    std::string name_;
    unsigned int id_ = 0;
  };
}
