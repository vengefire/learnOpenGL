#pragma once

#include "../../config.h"

namespace openGL::models
{
  class ModelBase
  {
  public:
    ModelBase();
    virtual ~ModelBase();

    std::vector<float> get_vertices() const;
    void set_vertices(std::vector<float> vertices);
    void set_indices(std::vector<unsigned int> indices);

    void render();

  protected:
    void buffer_vertex_data();

  private:
    void Init();
    std::vector<float> vertices_;
    std::vector<unsigned int> indices_;
    unsigned int vao_Id_ = -1;
    unsigned int vbo_Id_ = -1;
    unsigned int ebo_Id_ = -1;
  };

}
