#ifndef QTSPACE_MESH_H
#define QTSPACE_MESH_H

#include <vector>
#include <memory>

#include "Resource.h"

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
        kTangent0,
        kTangent1,
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
        kTangent0 = 3,
        kTangent1 = 3,
        kNumPropertyTyp
    };
}

struct VertexSemantic {
    VertexSemantic(bool has_normal,
                   bool has_uv0,
                   bool has_uv1,
                   bool has_color,
                   bool has_tangent0,
                   bool has_tangent1);

    size_t vertex_size = 0;
    size_t position_offset = 0;
    size_t normal_offset = 0;
    size_t uv0_offset = 0;
    size_t uv1_offset = 0;
    size_t color_offset = 0;
    size_t tangent0_offset = 0;
    size_t tangent1_offset = 0;
};

typedef shared_ptr<VertexSemantic> VertexSemanticPtr;
typedef shared_ptr<const VertexSemantic> kVertexSemanticPtr;

class Mesh : public Resource {
public:
    Mesh(vector<float> &vertex_buffer,
         kVertexSemanticPtr &vertex_semantic);

    size_t vertex_size() const;

    size_t position_offset() const;

    size_t normal_offset() const;

    size_t uv0_offset() const;

    size_t uv1_offset() const;

    size_t color_offset() const;

    size_t vertex_buffer_size() const;

    const vector<float> &vertex_buffer() const;

private:
    size_t num_vertices_;
    kVertexSemanticPtr vertex_semantic_;
    vector<float> vertex_buffer_;
};

#endif //QTSPACE_MESH_H
