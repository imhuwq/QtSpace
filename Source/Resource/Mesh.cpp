#include "Mesh.h"

VertexSemantic::VertexSemantic(bool has_normal,
                               bool has_uv0,
                               bool has_uv1,
                               bool has_color,
                               bool has_tangent0,
                               bool has_tangent1) {
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
    if (has_tangent0) {
        tangent0_offset = vertex_size;
        vertex_size += VertexPropertySize::kTangent0;
    }
    if (has_tangent1) {
        tangent1_offset = vertex_size;
        vertex_size += VertexPropertySize::kTangent1;
    }
}


Mesh::Mesh(vector<float> &vertex_buffer,
           kVertexSemanticPtr &vertex_semantic) : vertex_semantic_(vertex_semantic) {
    vertex_buffer_ = std::move(vertex_buffer);
    num_vertices_ = vertex_buffer_.size() / vertex_semantic->vertex_size;
}

size_t Mesh::vertex_size() const { return vertex_semantic_->vertex_size; }

size_t Mesh::position_offset() const { return vertex_semantic_->position_offset; }

size_t Mesh::normal_offset() const { return vertex_semantic_->normal_offset; }

size_t Mesh::uv0_offset() const { return vertex_semantic_->uv0_offset; }

size_t Mesh::uv1_offset() const { return vertex_semantic_->uv1_offset; }

size_t Mesh::color_offset() const { return vertex_semantic_->color_offset; }

size_t Mesh::vertex_buffer_size() const { return vertex_buffer_.size(); }

const vector<float> &Mesh::vertex_buffer() const { return vertex_buffer_; }
