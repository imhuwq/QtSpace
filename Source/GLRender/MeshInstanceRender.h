#ifndef QTSPACE_MESHINSTANCERENDER_H
#define QTSPACE_MESHINSTANCERENDER_H

#include <memory>

#include "Resource/Material.h"
#include "Resource/Mesh.h"
#include "Resource/GraphNode/Node.h"
#include "Resource/GraphNode/MeshInstance.h"
#include "Shader.h"

using namespace std;

struct MeshInstanceRender;

typedef shared_ptr<MeshInstanceRender> MeshInstanceRenderPtr;
typedef shared_ptr<const MeshInstanceRender> kMeshInstanceRenderPtr;

struct MeshInstanceRender {
    MeshInstanceRender(const kNodePtr &node,
                       size_t index_buffer_size,
                       size_t vertex_buffer_offset,
                       size_t index_buffer_offset,
                       const QMatrix4x4 &transformation);

    kNodePtr node;
    QMatrix4x4 transformation;
    size_t vertex_buffer_offset;
    size_t index_buffer_offset;
    size_t index_buffer_size;
};

#endif //QTSPACE_MESHINSTANCERENDER_H
