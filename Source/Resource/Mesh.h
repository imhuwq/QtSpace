#ifndef QTSPACE_MESH_H
#define QTSPACE_MESH_H

#include <vector>
#include <memory>

#include "Resource.h"
#include "Common/TypeDef.h"
#include "ModelLoader/VertexSemantic.h"

class Mesh : public Resource {
public:
    Mesh(std::vector<float> &vertex_buffer,
         kVertexSemanticPtr &vertex_semantic);

    size_t vertex_size() const;

    size_t position_offset() const;

    size_t normal_offset() const;

    size_t uv0_offset() const;

    size_t uv1_offset() const;

    size_t color_offset() const;

    size_t vertex_buffer_size() const;

    const std::vector<float> &vertex_buffer() const;

private:
    size_t num_vertices_;
    kVertexSemanticPtr vertex_semantic_;
	std::vector<float> vertex_buffer_;
};

#endif //QTSPACE_MESH_H
