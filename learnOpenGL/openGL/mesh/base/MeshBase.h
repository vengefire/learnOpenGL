#pragma once
#include <vector>
#include "VertexBase.h"

namespace openGL::mesh
{
  class MeshBase
  {
  public:
    MeshBase() = default;
    MeshBase(const std::vector<base::VertexBase>& vertices, const std::vector<unsigned int>& indices,
             const glm::vec4& default_color = { 0.5f, 0.5f, 0.5f, 0.5f })
      : MeshBase(vertices, default_color)
    {
      indices_ = indices;
    }

    MeshBase(const std::vector<base::VertexBase>& vertices, const glm::vec4& default_color = {0.5f, 0.5f, 0.5f, 0.5f})
      : vertices_(vertices),
        default_color_(default_color)
    {
    }

    std::vector<float> get_formatted_vertices() const
    {
      std::vector<float> vertex_data;
      for (const auto& vertex : vertices_)
      {
        const auto& position = vertex.get_position().PropertyValue;
        vertex_data.insert(vertex_data.end(), { position.x, position.y, position.z });

        if (vertex.Normal.HasValue)
        {
          vertex_data.insert(vertex_data.end(), { vertex.Normal.X, vertex.Normal.Y, vertex.Normal.Z });
        }

        if (vertex.Color.HasValue)
        {
          const auto& color = vertex.Color;
          vertex_data.insert(vertex_data.end(), { color.R(), color.G(), color.B(), color.A() });
        }
        else if (default_color_.HasValue)
        {
          vertex_data.insert(vertex_data.end(), { default_color_.R(), default_color_.G(), default_color_.B(),  default_color_.A() });
        }
        if (vertex.TextureCoordinates.HasValue)
        {
          const auto& tex_coords = vertex.get_texture_coordinates();
          vertex_data.insert(vertex_data.end(), { tex_coords.U(), tex_coords.V() });
        }
      }
      return vertex_data;
    }

    bool vertices_have_normals() const
    {
      return !vertices_.empty() && vertices_[0].Normal.HasValue;
    }

    bool vertices_have_color() const
    {
      return !vertices_.empty() && (vertices_[0].Color.HasValue || default_color_.HasValue);
    }

    bool vertices_have_texture_coordinates() const
    {
      return !vertices_.empty() && vertices_[0].TextureCoordinates.HasValue;
    }

  protected:
    std::vector<base::VertexBase> vertices_;
    std::vector<unsigned int> indices_;
    entity::property::EntityPropertyColor default_color_;
    bool draw_lines_ = false; // Flag to indicate if the mesh should be drawn as lines

  public:
    [[nodiscard]] bool draw_lines() const
    {
      return draw_lines_;
    }

    void set_draw_lines(const bool draw_lines)
    {
      draw_lines_ = draw_lines;
    }

    __declspec(property(get = draw_lines, put = set_draw_lines)) bool DrawLines;

    [[nodiscard]] std::vector<base::VertexBase> vertices() const
    {
      return vertices_;
    }

    void set_vertices(const std::vector<base::VertexBase>& vertices)
    {
      vertices_ = vertices;
    }

    __declspec(property(get = vertices, put = set_vertices)) std::vector<base::VertexBase> Vertices;

    [[nodiscard]] std::vector<unsigned int> indices() const
    {
      return indices_;
    }

    void set_indices(const std::vector<unsigned int>& indices)
    {
      indices_ = indices;
    }

    __declspec(property(get = indices, put = set_indices)) std::vector<unsigned int> Indices;

    [[nodiscard]] entity::property::EntityPropertyColor default_color() const
    {
      return default_color_;
    }

    void set_default_color(const entity::property::EntityPropertyColor& default_color)
    {
      default_color_ = default_color;
    }

    __declspec(property(get = default_color, put = set_default_color)) entity::property::EntityPropertyColor
    DefaultColor;
  };
}
