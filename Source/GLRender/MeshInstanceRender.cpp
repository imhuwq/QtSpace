#include "GLRender/MeshInstanceRender.h"

MeshInstanceRender::MeshInstanceRender(const kNodePtr &node,
                                       size_t index_buffer_size,
                                       size_t vertex_buffer_offset,
                                       size_t index_buffer_offset,
                                       const QMatrix4x4 &transformation) : node(node),
                                                                           transformation(transformation),
                                                                           index_buffer_size(index_buffer_size),
                                                                           vertex_buffer_offset(vertex_buffer_offset),
                                                                           index_buffer_offset(index_buffer_offset) {

}