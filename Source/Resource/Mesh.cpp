#include "Mesh.h"

VertexSemantic::VertexSemantic(bool has_normal,
                               bool has_uv0,
                               bool has_uv1,
                               bool has_color,
                               bool has_blend) : has_blend(has_blend) {
    position_offset = 0;
    vertex_size += VertexPropertySize::kPosition;

    if (has_normal) {
        normal_offset = vertex_size;
        vertex_size += VertexPropertySize::kNormal;
    }
    if (has_uv0) {
        uv0_offset = vertex_size;
        vertex_size += VertexPropertySize::kUV0;
    }
    if (has_uv1) {
        uv1_offset = vertex_size;
        vertex_size += VertexPropertySize::kUV1;
    }
    if (has_color) {
        color_offset = vertex_size;
        vertex_size += VertexPropertySize::kColor;
    }
}


Mesh::Mesh(size_t num_vertices,
           const VertexSemantic &vertex_semantic) : num_vertices_(num_vertices),
                                                    vertex_semantic_(vertex_semantic) {
    num_vertices_ = num_vertices;
    vertex_buffer_.resize(vertex_semantic_.vertex_size * num_vertices_);
    if (vertex_semantic_.has_blend) {
        blend_indices_buffer_.resize(VertexPropertySize::kBlendIndices * num_vertices_);
        blend_weights_buffer_.resize(VertexPropertySize::kBlendWeights * num_vertices_);
    }
}

size_t Mesh::vertex_size() const { return vertex_semantic_.vertex_size; }

size_t Mesh::position_offset() const { return vertex_semantic_.position_offset; }

size_t Mesh::normal_offset() const { return vertex_semantic_.normal_offset; }

size_t Mesh::uv0_offset() const { return vertex_semantic_.uv0_offset; }

size_t Mesh::uv1_offset() const { return vertex_semantic_.uv1_offset; }

size_t Mesh::color_offset() const { return vertex_semantic_.color_offset; }

void Mesh::SetVertex(const vector<float> &vertex_data,
                     size_t index,
                     const vector<float> &blend_weights,
                     const vector<unsigned int> &blend_indices) {
    size_t pos = vertex_semantic_.vertex_size * index;
    for (size_t i = 0; i < vertex_semantic_.vertex_size; i++) vertex_buffer_[pos + i] = vertex_data[i];

    if (vertex_semantic_.has_blend && !blend_weights.empty() && !blend_indices.empty()) {
        pos = 4 * index;
        for (size_t i = 0; i < VertexPropertySize::kBlendIndices; i++) {
            blend_weights_buffer_[pos + i] = blend_weights[i];
            blend_indices_buffer_[pos + i] = blend_indices[i];
        }
    }
}

void Mesh::SetBuffers(const vector<float> &vertex_buffer,
                      const vector<float> &blend_weights_buffer,
                      const vector<unsigned int> &blend_indices_buffer) {
    vertex_buffer_ = vertex_buffer;
    blend_weights_buffer_ = blend_weights_buffer;
    blend_indices_buffer_ = blend_indices_buffer;
}

size_t Mesh::vertex_buffer_size() const { return vertex_buffer_.size(); }

const vector<float> &Mesh::vertex_buffer() const { return vertex_buffer_; }
