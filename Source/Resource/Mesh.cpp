#include "Mesh.h"

using namespace std;

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
