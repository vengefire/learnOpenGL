#include "ModelBase.h"

#include <utility>

namespace openGL::models
{
  ModelBase::ModelBase()
  {
    Init();
  }

  ModelBase::~ModelBase()
  {
  }

  std::vector<float> ModelBase::get_vertices() const
  {
    return vertices_;
  }

  void ModelBase::set_vertices(std::vector<float> vertices)
  {
    vertices_ = std::move(vertices);
    buffer_vertex_data();
  }

  void ModelBase::set_indices(std::vector<unsigned int> indices)
  {
    indices_ = std::move(indices);
    glGenBuffers(1, &ebo_Id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_Id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);
  }

  void ModelBase::render()
  {
    auto triangles_to_render = indices_.empty() ? vertices_.size() / 6 : indices_.size();
    glBindVertexArray(vao_Id_);

    if (texture_)
    {
      texture_->bind();
    }

    shader_program_->use();

    if (!indices_.empty())
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_Id_);
      glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(triangles_to_render), GL_UNSIGNED_INT, nullptr);
    }
    else
    {
      glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(triangles_to_render));
    }
    glBindVertexArray(0);
  }

  void ModelBase::buffer_vertex_data()
  {
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);
  }

  void ModelBase::Init()
  {
    glGenVertexArrays(1, &vao_Id_);
    glGenBuffers(1, &vbo_Id_);
    glBindVertexArray(vao_Id_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Id_);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  }

  void ModelBase::set_texture_from_file(const std::string& textureFilePath)
  {
    if (!texture_)
    {
      texture_ = std::make_shared<textures::TextureBase>();
    }
    texture_->loadFromFile(textureFilePath);
  }

}
