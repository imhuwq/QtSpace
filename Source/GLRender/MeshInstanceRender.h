#ifndef QTSPACE_MESHINSTANCERENDER_H
#define QTSPACE_MESHINSTANCERENDER_H

#include "Common/Consts.h"
#include "Common/TypeDef.h"
#include "Resource/Material.h"
#include "Resource/Mesh.h"
#include "Resource/GraphNode/Node.h"
#include "Resource/GraphNode/MeshInstance.h"

using namespace std;

class MeshInstanceRender {
public:
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
