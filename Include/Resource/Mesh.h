#ifndef QTSPACE_MESH_H
#define QTSPACE_MESH_H

#include <vector>
#include <memory>

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "Resource/Resource.h"

using namespace std;

class Mesh;

typedef shared_ptr<Mesh> MeshPtr;
typedef shared_ptr<const Mesh> kMeshPtr;

namespace VertexPropertyType {
    enum Type {
        kGeneral = 0,
        kPosition,
        kNormal,
        kUV0,
        kUV1,
        kColors,
        kBlendWeights,
        kBlendIndices,
        kNumPropertyType
    };
}

namespace VertexPropertySize {
    enum Size {
        kGeneral = 0,
        kPosition = 3,
        kNormal = 3,
        kUV0 = 2,
        kUV1 = 2,
        kColor = 4,
        kBlendWeights = 4,
        kBlendIndices = 4,
        kNumPropertyTyp
    };
}



struct Vertex {
    Vertex() : positions(3),
               normals(3),
               uvs0(2),
               uvs1(2),
               colors(4),
               blend_weights(4),
               blend_indices(4) {}

    vector<float> positions;
    vector<float> normals;
    vector<float> uvs0;
    vector<float> uvs1;
    vector<float> colors;
    vector<float> blend_weights;
    vector<unsigned int> blend_indices;
};

class Mesh : public Resource {
public:
    Mesh(size_t num_vertices,
         bool has_normal = false,
         bool has_uv0 = false,
         bool has_uv1 = false,
         bool has_color = false,
         bool has_blend_weights = false,
         bool has_blend_indices = false) {
        num_vertices_ = num_vertices;
        position_offset_ = 0;
        vertex_size_ += VertexPropertySize::kPosition;

        if (has_normal) {
            normal_offset_ = vertex_size_;
            vertex_size_ += VertexPropertySize::kNormal;
        }
        if (has_uv0) {
            uv0_offset_ = vertex_size_;
            vertex_size_ += VertexPropertySize::kUV0;
        }
        if (has_uv1) {
            uv1_offset_ = vertex_size_;
            vertex_size_ += VertexPropertySize::kUV1;
        }
        if (has_color) {
            color_offset_ = vertex_size_;
            vertex_size_ += VertexPropertySize::kColor;
        }
        vertex_buffer_.resize(vertex_size_ * num_vertices_);

        if (has_blend_indices && has_blend_weights) {
            blend_indices_buffer_.resize(VertexPropertySize::kBlendIndices * num_vertices_);
            blend_weights_buffer_.resize(VertexPropertySize::kBlendWeights * num_vertices_);
        }
    }

    size_t vertex_size() const { return vertex_size_; }

    size_t position_offset() const { return position_offset_; }

    size_t normal_offset() const { return normal_offset_; }

    size_t uv0_offset() const { return uv0_offset_; }

    size_t uv1_offset() const { return uv1_offset_; }

    size_t color_offset() const { return color_offset_; }

    Vertex GetVertex(size_t index) {
        Vertex vertex;
        size_t pos = vertex_size_ * index;
        size_t idx = pos + position_offset_;

        for (size_t i = 0; i < VertexPropertySize::kPosition; i++) vertex.positions[i] = vertex_buffer_[idx + i];

        if (normal_offset_) {
            idx = pos + normal_offset_;
            for (size_t i = 0; i < VertexPropertySize::kNormal; i++) vertex.normals[i] = vertex_buffer_[idx + i];
        }

        if (uv0_offset_) {
            idx = pos + uv0_offset_;
            for (size_t i = 0; i < VertexPropertySize::kUV0; i++) vertex.uvs0[i] = vertex_buffer_[idx + i];
        }

        if (uv1_offset_) {
            idx = pos + uv1_offset_;
            for (size_t i = 0; i < VertexPropertySize::kUV1; i++) vertex.uvs1[i] = vertex_buffer_[idx + i];
        }

        if (color_offset_) {
            idx = pos + color_offset_;
            for (size_t i = 0; i < VertexPropertySize::kColor; i++) vertex.colors[i] = vertex_buffer_[idx + i];
        }

        if (!blend_indices_buffer_.empty() && !blend_weights_buffer_.empty()) {
            idx = 4 * index;
            for (size_t i = 0; i < VertexPropertySize::kBlendWeights; i++) {
                vertex.blend_weights[i] = blend_weights_buffer_[idx + i];
                vertex.blend_indices[i] = blend_indices_buffer_[idx + i];
            }
        }

        return std::move(vertex);
    }

    void SetVertex(const Vertex &vertex, size_t index) {
        size_t pos = vertex_size_ * index;
        size_t idx = pos + position_offset_;

        for (size_t i = 0; i < VertexPropertySize::kPosition; i++) vertex_buffer_[idx + i] = vertex.positions[i];

        if (normal_offset_ && !vertex.normals.empty()) {
            idx = pos + normal_offset_;
            for (size_t i = 0; i < VertexPropertySize::kNormal; i++) vertex_buffer_[idx + i] = vertex.normals[i];
        }

        if (uv0_offset_) {
            idx = pos + uv0_offset_;
            for (size_t i = 0; i < VertexPropertySize::kUV0; i++) vertex_buffer_[idx + i] = vertex.uvs0[i];
        }

        if (uv1_offset_) {
            idx = pos + uv1_offset_;
            for (size_t i = 0; i < VertexPropertySize::kUV1; i++) vertex_buffer_[idx + i] = vertex.uvs1[i];
        }

        if (color_offset_) {
            idx = pos + color_offset_;
            for (size_t i = 0; i < VertexPropertySize::kColor; i++) vertex_buffer_[idx + i] = vertex.colors[i];
        }

        if (!blend_indices_buffer_.empty() && !vertex.blend_indices.empty()) {
            idx = 4 * index;
            for (size_t i = 0; i < VertexPropertySize::kBlendIndices; i++) {
                blend_indices_buffer_[idx + i] = vertex.blend_indices[i];
                blend_weights_buffer_[idx + i] = vertex.blend_weights[i];
            }
        }
    }

    size_t vertex_buffer_size() const { return vertex_buffer_.size(); }

    const vector<float> &vertex_buffer() const { return vertex_buffer_; }

private:
    size_t num_vertices_;

    vector<float> vertex_buffer_;
    size_t vertex_size_ = 0;
    size_t position_offset_ = 0;
    size_t normal_offset_ = 0;
    size_t uv0_offset_ = 0;
    size_t uv1_offset_ = 0;
    size_t color_offset_ = 0;

    vector<float> blend_weights_buffer_;
    vector<unsigned int> blend_indices_buffer_;
};

#endif //QTSPACE_MESH_H
