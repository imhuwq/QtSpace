#ifndef QTSPACE_MESH_H
#define QTSPACE_MESH_H

#include <vector>
#include <memory>

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
                   bool has_blend);

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
         const VertexSemantic &vertex_semantic);

    size_t vertex_size() const;

    size_t position_offset() const;

    size_t normal_offset() const;

    size_t uv0_offset() const;

    size_t uv1_offset() const;

    size_t color_offset() const;

    void SetVertex(const vector<float> &vertex_data,
                   size_t index,
                   const vector<float> &blend_weights = {},
                   const vector<unsigned int> &blend_indices = {});

    void SetBuffers(const vector<float> &vertex_buffer,
                    const vector<float> &blend_weights_buffer = {},
                    const vector<unsigned int> &blend_indices_buffer = {});

    size_t vertex_buffer_size() const;

    const vector<float> &vertex_buffer() const;

private:
    size_t num_vertices_;
    VertexSemantic vertex_semantic_;
    vector<float> vertex_buffer_;
    vector<float> blend_weights_buffer_;
    vector<unsigned int> blend_indices_buffer_;
};

#endif //QTSPACE_MESH_H
