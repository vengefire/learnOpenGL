#include "ModelBase.h"

namespace openGL::model
{
  ModelBase::ModelBase(mesh::MeshBase mesh, const std::shared_ptr<shaders::ShaderProgram>& shader_program, const std::shared_ptr<camera::CameraBase>& camera) :
    shader_program_(shader_program),
    camera_(camera)
  {
    Mesh = mesh;
  }

  ModelBase::~ModelBase()
  {
    std::cout << "ModelBaseDep Destructor called, deleting VAO: " << vao_id_ << std::endl;
    glDeleteVertexArrays(1, &vao_id_);
    std::cout << "ModelBaseDep Destructor called, deleting VBO: " << vbo_id_ << std::endl;
    glDeleteBuffers(1, &vbo_id_);
    if (ebo_id_ != 0)
    {
      std::cout << "ModelBaseDep Destructor called, deleting EBO: " << ebo_id_ << std::endl;
      glDeleteBuffers(1, &ebo_id_);
    }
  }

  void ModelBase::renderModel()
  {
    shader_program_->use();
    if (shader_program_->OnRender)
    {
      shader_program_->OnRender(shader_program_);
    }

    // Generate an identity matrix
    glm::mat4 trans = calculate_translation();
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

    glBindVertexArray(vao_id_);
    auto count = Mesh.Indices.empty() ? Mesh.Vertices.size() : Mesh.Indices.size();

    if (!Mesh.Indices.empty())
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id_);
      glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(count), GL_UNSIGNED_INT, nullptr);
    }
    else
    {
      GLenum mode = GL_TRIANGLES;

      if (Mesh.DrawLines)
      {
        mode = GL_LINES;
      }

      glDrawArrays(mode, 0, static_cast<GLsizei>(count));
    }
    glBindVertexArray(0);
  }

  void ModelBase::set_texture_from_file(const std::string& textureFilePath, bool flip_vertically)
  {
    auto texture_ = std::make_shared<textures::TextureBase>();
    texture_->loadFromFile(textureFilePath, flip_vertically);
    set_texture(texture_);
  }

  void ModelBase::set_texture(const std::shared_ptr<textures::TextureBase>& texture)
  {
    textures_.push_back(texture);
  }

  void ModelBase::initialize_buffers()
  {
    if (vao_id_ == 0)
    {
      glGenVertexArrays(1, &vao_id_);
      glBindVertexArray(vao_id_);
    }
    if (vbo_id_ == 0)
    {
      glGenBuffers(1, &vbo_id_);
      glBindBuffer(GL_ARRAY_BUFFER, vbo_id_);
    }
    if (!Mesh.Indices.empty() && ebo_id_ == 0)
    {
      glGenBuffers(1, &ebo_id_);
    }
  }

  void ModelBase::upload_vertex_data()
  {
    auto vertices = mesh_.get_formatted_vertices();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  }

  void ModelBase::configure_vertex_attributes()
  {
    int floatCount = 3; // Position
    int offset = 0;
    unsigned int position = 0;
    floatCount += Mesh.vertices_have_normals() ? 3 : 0; // Color
    floatCount += Mesh.vertices_have_color() ? 4 : 0; // Color
    floatCount += Mesh.vertices_have_texture_coordinates() ? 2 : 0; // Texture Coordinates
    int stride = floatCount * static_cast<int>(sizeof(float));

    // Position Mandatory
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, stride, static_cast<void*>(nullptr));
    offset += 3 * sizeof(float);
    glEnableVertexAttribArray(position++);

    // Normals Optional
    if (Mesh.vertices_have_normals())
    {
      glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
      glEnableVertexAttribArray(position++);
      offset += 3 * sizeof(float);
    }

    // Color Optional
    if (Mesh.vertices_have_color())
    {
      glVertexAttribPointer(position, 4, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
      glEnableVertexAttribArray(position++);
      offset += 4 * sizeof(float);
    }

    // Texture Coordinates Optional
    if (Mesh.vertices_have_texture_coordinates())
    {
      glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
      glEnableVertexAttribArray(position++);
      offset += 2 * sizeof(float);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void ModelBase::upload_indices_data()
  {
    if (!Mesh.Indices.empty())
    {
      auto indices = Mesh.Indices;
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id_);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }
  }

  void ModelBase::set_mesh(const mesh::MeshBase& mesh)
  {
    mesh_ = mesh;
    initialize_buffers();
    upload_vertex_data();
    configure_vertex_attributes();
    upload_indices_data();
  }
}
