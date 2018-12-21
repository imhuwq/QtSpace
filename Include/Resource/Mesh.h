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


struct VertexSemantic {
    VertexSemantic(bool has_normal,
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

    size_t vertex_size = 0;
    size_t position_offset = 0;
    size_t normal_offset = 0;
    size_t uv0_offset = 0;
    size_t uv1_offset = 0;
    size_t color_offset = 0;
    bool has_blend;
};


class Mesh : public Resource {
public:
    Mesh(size_t num_vertices,
         const VertexSemantic &vertex_semantic) : num_vertices_(num_vertices),
                                                  vertex_semantic_(vertex_semantic) {
        num_vertices_ = num_vertices;
        vertex_buffer_.resize(vertex_semantic_.vertex_size * num_vertices_);
        if (vertex_semantic_.has_blend) {
            blend_indices_buffer_.resize(VertexPropertySize::kBlendIndices * num_vertices_);
            blend_weights_buffer_.resize(VertexPropertySize::kBlendWeights * num_vertices_);
        }
    }

    size_t vertex_size() const { return vertex_semantic_.vertex_size; }

    size_t position_offset() const { return vertex_semantic_.position_offset; }

    size_t normal_offset() const { return vertex_semantic_.normal_offset; }

    size_t uv0_offset() const { return vertex_semantic_.uv0_offset; }

    size_t uv1_offset() const { return vertex_semantic_.uv1_offset; }

    size_t color_offset() const { return vertex_semantic_.color_offset; }

    void SetVertex(const vector<float> &vertex_data, size_t index, const vector<float> &blend_weights = {}, const vector<unsigned int> &blend_indices = {}) {
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

    void SetBuffers(const vector<float> &vertex_buffer, const vector<float> &blend_weights_buffer = {}, const vector<unsigned int> &blend_indices_buffer = {}) {
        vertex_buffer_ = vertex_buffer;
        blend_weights_buffer_ = blend_weights_buffer;
        blend_indices_buffer_ = blend_indices_buffer;
    }

    size_t vertex_buffer_size() const { return vertex_buffer_.size(); }

    const vector<float> &vertex_buffer() const { return vertex_buffer_; }

private:
    size_t num_vertices_;
    VertexSemantic vertex_semantic_;
    vector<float> vertex_buffer_;
    vector<float> blend_weights_buffer_;
    vector<unsigned int> blend_indices_buffer_;
};

#endif //QTSPACE_MESH_H
