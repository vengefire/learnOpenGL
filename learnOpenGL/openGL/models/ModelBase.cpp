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
    std::cout << "ModelBase Destructor called, deleting VAO: " << vao_Id_ << std::endl;
    glDeleteVertexArrays(1, &vao_Id_);
    std::cout << "ModelBase Destructor called, deleting VBO: " << vbo_Id_ << std::endl;
    glDeleteBuffers(1, &vbo_Id_);
    if (ebo_Id_ != -1)
    {
      std::cout << "ModelBase Destructor called, deleting EBO: " << ebo_Id_ << std::endl;
      glDeleteBuffers(1, &ebo_Id_);
    }
  }

  std::vector<float> ModelBase::get_vertices() const
  {
    return vertices_;
  }

  void ModelBase::set_vertices(std::vector<core::VertexBase> vertices)
  {
    vertices_data_ = std::move(vertices);
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
    shader_program_->use();

    int textureCnt = 0;
    for (const auto& texture : textures_)
    {
      shader_program_->set_int(std::format("texture{}", textureCnt + 1), textureCnt); // Set texture unit X for textureX
      texture->bind(textureCnt++);
    }

    glBindVertexArray(vao_Id_);
    auto count = indices_.empty() ? vertices_data_.size() : indices_.size();
    if (!indices_.empty())
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_Id_);
      glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr);
    }
    else
    {
      glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(count));
    }
    glBindVertexArray(0);
  }

  void ModelBase::buffer_vertex_data()
  {
    glBindVertexArray(vao_Id_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_Id_);

    std::vector<float> vertexData;
    for (auto vertices_data : vertices_data_)
    {
      float position[3] = {
        vertices_data.get_position_x(), vertices_data.get_position_y(), vertices_data.get_position_z()
      };
      vertexData.insert(vertexData.end(), position, position + 3);
      if (vertices_data.hasColor())
      {
        float colorData[3] = {vertices_data.get_color_r(), vertices_data.get_color_g(), vertices_data.get_color_b()};
        vertexData.insert(vertexData.end(), colorData, colorData + 3);
      }
      if (vertices_data.hasTextureCoordinates())
      {
        float textureCoords[2] = {vertices_data.get_texture_coordinate_u(), vertices_data.get_texture_coordinate_v()};
        vertexData.insert(vertexData.end(), textureCoords, textureCoords + 2);
      }
    }
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    int floatCount = 3; // Position
    int offset = 0;
    unsigned int position = 0;
    floatCount += vertices_data_[0].hasColor() ? 3 : 0; // Color
    floatCount += vertices_data_[0].hasTextureCoordinates() ? 2 : 0; // Texture Coordinates
    int stride = floatCount * sizeof(float);

    // Position Mandatory
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, stride, static_cast<void*>(nullptr));
    offset += 3 * sizeof(float);
    glEnableVertexAttribArray(position++);
    // Color Optional
    if (vertices_data_[0].hasColor())
    {
      glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
      glEnableVertexAttribArray(position++);
      offset += 3 * sizeof(float);
    }
    // Texture Coordinates Optional
    if (vertices_data_[0].hasTextureCoordinates())
    {
      glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
      glEnableVertexAttribArray(position++);
      offset += 2 * sizeof(float);
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void ModelBase::Init()
  {
    glGenVertexArrays(1, &vao_Id_);
    glGenBuffers(1, &vbo_Id_);
  }

  void ModelBase::set_texture_from_file(const std::string& textureFilePath, bool flip_vertically)
  {
    auto texture_ = std::make_shared<textures::TextureBase>();
    texture_->loadFromFile(textureFilePath, flip_vertically);
    set_texture(texture_);
  }
}
