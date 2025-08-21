#pragma once
#include <functional>
#include <glm/detail/type_vec.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "CartesianPrimitiveBase.h"
#include "TypedPrimitiveBase.h"

namespace openGL::primitives
{
  class CubePrimitive :
    public TypedPrimitiveBase<CubePrimitive>
  {
  public:
    CubePrimitive(entity::property::EntityPropertyDimensions dimensions) : TypedPrimitiveBase(dimensions)
    {
    }

    static CubePrimitive generate_cube_primitive(float width = 1.0f, float height = 1.0f, float depth = 1.0f)
    {
      auto cubePrimitive = CubePrimitive(glm::vec3{ width, height, depth });
      return TypedPrimitiveBase::generate_primitive(cubePrimitive);
    }

    mesh::MeshBase generate_primitive_mesh() override
    {
      auto half_width = Dimensions.Width / 2.0f;
      auto half_height = Dimensions.Height / 2.0f;
      auto half_depth = Dimensions.Depth / 2.0f;

      // Generate vertices for a cube centered at the origin
      std::vector<glm::vec4> front_face = {
        // Front Face - BottomLeft-BottomRight-TopRight-TopLeft : Indices 0,1,2-2,3,0
        {-half_width, -half_height, half_depth, 1},
        {half_width, -half_height, half_depth, 1},
        {half_width, half_height, half_depth, 1},
        {-half_width, half_height, half_depth, 1}
      };

      std::vector<glm::vec2> front_face_texels = {
        { 0.0f, 0.0f}, // Bottom Left
        { 1.0f, 0.0f}, // Bottom Right
        { 1.0f, 1.0f}, // Top Right
        { 0.0f, 1.0f}  // Top Left
      };


      std::function<void(const std::vector<glm::vec4>&)> add_vertices = [this, front_face_texels](const std::vector<glm::vec4>& vertices)
      {
        for (int index = 0; index < vertices.size(); ++index)
        {
          // Add texture coordinates to the vertex
          this->_vertices.emplace_back(vertices[index].x, vertices[index].y, vertices[index].z,front_face_texels[index].x, front_face_texels[index].y);
        }
      };

      std::function<void(unsigned int)> add_indices = [this](unsigned int offset)
      {
        // First triangle
        this->_indices.emplace_back(offset);
        this->_indices.emplace_back(offset + 1);
        this->_indices.emplace_back(offset + 2);
        // Second triangle
        this->_indices.emplace_back(offset + 2);
        this->_indices.emplace_back(offset + 3);
        this->_indices.emplace_back(offset);
      };

      unsigned int indexOffset = 0;

      // Use matrix translations to generate the other faces
      auto translate = [](const std::vector<glm::vec4>& face, const glm::vec3& translation, const glm::vec3& rotation)
      {
        std::vector<glm::vec4> translated_face;
        for (auto& vertex : face)
        {
          auto translatedMatrix = glm::translate(glm::mat4(1.0f), translation);
          translatedMatrix = glm::rotate(translatedMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
          translatedMatrix = glm::rotate(translatedMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
          translatedMatrix = glm::rotate(translatedMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
          translated_face.emplace_back(translatedMatrix * glm::vec4(vertex.x, vertex.y, vertex.z, 1.0f));
        }
        return translated_face;
      };

      auto generate_face = [this, &add_vertices, &add_indices, &indexOffset, &translate](const std::vector<glm::vec4>& face, const glm::vec3& translation, const glm::vec3& rotation)
      {
        auto translated_face = translate(face, translation, rotation);
        add_vertices(translated_face);
        add_indices(indexOffset);
        indexOffset += 4;
      };

      generate_face(front_face, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Front face
      generate_face(front_face, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 180.0f, 0.0f)); // Back face
      generate_face(front_face, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 90.0f, 0.0f)); // Right face
      generate_face(front_face, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -90.0f, 0.0f)); // Left face
      generate_face(front_face, glm::vec3(0, 0.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)); // Top face
      generate_face(front_face, glm::vec3(0, 0.0f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f)); // Bottom face

      return { _vertices, _indices };
    }
  };
}
