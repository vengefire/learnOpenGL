#include "ModelBase.h"

#include <utility>
#include <../../dep/glm/glm.hpp>
#include <../../dep/glm/gtc/matrix_transform.hpp>
#include <../../dep/glm/gtc/type_ptr.hpp>

namespace openGL::models
{
  ModelBase::ModelBase()
  {
    Init();
  }

  ModelBase::ModelBase(std::shared_ptr<shaders::ShaderProgram>shaderProgram) : shader_program_(std::move(shaderProgram))
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

  void ModelBase::draw_elements_or_arrays(std::vector<core::VertexBase>::size_type count) const
  {
    if (!indices_.empty())
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_Id_);
      glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr);
    }
    else if (!draw_lines)
    {
      glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(count));
    }
    else
    {
      glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(count));
    }
  }

  void ModelBase::render()
  {
    shader_program_->use();

    // Gen an identity matrix
    glm::mat4 trans = glm::mat4(1.0f);
    // Apply Scaling
    trans = glm::scale(trans, glm::vec3(scale_, scale_, scale_));
    // Apply translation
    trans = glm::translate(trans, glm::vec3(translationX_, translationY_, translationZ_));
    // Apply rotation
    trans = glm::rotate(trans, glm::radians(rotationX_), glm::vec3(1.0, 0.0, 0.0));
    trans = glm::rotate(trans, glm::radians(rotationY_), glm::vec3(0.0, 1.0, 0.0));
    trans = glm::rotate(trans, glm::radians(rotationZ_), glm::vec3(0.0, 0.0, 1.0));

    // view
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // Move the camera back
    view = camera_ ? camera_->getViewMatrix() : view;

    // projection
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    projection = camera_ ? camera_->get_projection_matrix() : projection;

    shader_program_->set_mat4("transform", trans);
    shader_program_->set_mat4("view", view);
    shader_program_->set_mat4("projection", projection);

    int textureCnt = 0;
    for (const auto& texture : textures_)
    {
      shader_program_->set_int(std::format("texture{}", textureCnt + 1), textureCnt); // Set texture unit X for textureX
      texture->bind(textureCnt++);
    }

    shader_program_->set_float("textureMix", textureMix_);

    glBindVertexArray(vao_Id_);
    auto count = indices_.empty() ? vertices_data_.size() : indices_.size();
    draw_elements_or_arrays(count);
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
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, stride, (void*)(0));
    offset += 3 * sizeof(float);
    glEnableVertexAttribArray(position++);
    // Color Optional
    if (vertices_data_[0].hasColor())
    {
      glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
      glEnableVertexAttribArray(position++);
      offset += 3 * sizeof(float);
    }
    // Texture Coordinates Optional
    if (vertices_data_[0].hasTextureCoordinates())
    {
      glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
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

  void ModelBase::handle_event(std::shared_ptr<events::ProcessInputEventData> pEventData)
  {

    // Blending
    if (glfwGetKey(pEventData->window, GLFW_KEY_1) == GLFW_PRESS)
    {
      textureMix_ += 0.01f;
    }
    else if (glfwGetKey(pEventData->window, GLFW_KEY_2) == GLFW_PRESS)
    {
      textureMix_ -= 0.01f;
    }

    // Scaling
    if (glfwGetKey(pEventData->window, GLFW_KEY_T) == GLFW_PRESS)
    {
      scale_ += 0.001f;
    }
    else if (glfwGetKey(pEventData->window, GLFW_KEY_G) == GLFW_PRESS)
    {
      scale_ -= 0.001f;
    }

    /*
    // Rotation
    if (glfwGetKey(pEventData->window, GLFW_KEY_A) == GLFW_PRESS)
    {
      yaw_ += 0.1f;
    }
    else if (glfwGetKey(pEventData->window, GLFW_KEY_D) == GLFW_PRESS)
    {
      yaw_ -= 0.1f;
    }

    if (glfwGetKey(pEventData->window, GLFW_KEY_W) == GLFW_PRESS)
    {
      pitch_ += 0.1f;
    }
    else if (glfwGetKey(pEventData->window, GLFW_KEY_S) == GLFW_PRESS)
    {
      pitch_ -= 0.1f;
    }

    if (glfwGetKey(pEventData->window, GLFW_KEY_Q) == GLFW_PRESS)
    {
      roll_ += 0.1f;
    }
    else if (glfwGetKey(pEventData->window, GLFW_KEY_E) == GLFW_PRESS)
    {
      roll_ -= 0.1f;
    }
    // Translation
    if (glfwGetKey(pEventData->window, GLFW_KEY_UP) == GLFW_PRESS)
    {
      translationZ_ += 0.1f;
    }
    else if (glfwGetKey(pEventData->window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
      translationZ_ -= 0.1f;
    }

    if (glfwGetKey(pEventData->window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
      translationX_ -= 0.1f;
    }
    else if (glfwGetKey(pEventData->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
      translationX_ += 0.1f;
    }

    if (glfwGetKey(pEventData->window, GLFW_KEY_R) == GLFW_PRESS)
    {
      translationY_ += 0.1f;
    }
    else if (glfwGetKey(pEventData->window, GLFW_KEY_F) == GLFW_PRESS)
    {
      translationY_ -= 0.1f;
    }
    */
  }

  void ModelBase::set_texture_from_file(const std::string& textureFilePath, bool flip_vertically)
  {
    auto texture_ = std::make_shared<textures::TextureBase>();
    texture_->loadFromFile(textureFilePath, flip_vertically);
    set_texture(texture_);
  }
}
