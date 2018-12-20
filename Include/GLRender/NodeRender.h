#ifndef QTSPACE_NODERENDER_H
#define QTSPACE_NODERENDER_H

#include <memory>

#include <QOpenGLShaderProgram>

#include "Resource/Material.h"
#include "Resource/Mesh.h"
#include "Resource/GraphNode/Node.h"
#include "Resource/GraphNode/MeshInstance.h"
#include "GLRender/Shader.h"

using namespace std;

class NodeRender;

typedef shared_ptr<NodeRender> NodeRenderPtr;
typedef shared_ptr<const NodeRender> kNodeRenderPtr;
typedef shared_ptr<QOpenGLShaderProgram> ShaderPtr;

class NodeRender {
public:
    NodeRender(const kNodePtr &node,
               size_t vertex_buffer_offset,
               size_t index_buffer_offset,
               const QMatrix4x4 &transformation) : node_(node),
                                                   transformation_(transformation),
                                                   vertex_buffer_offset_(vertex_buffer_offset),
                                                   index_buffer_offset_(index_buffer_offset) {}

    void Draw(const ShaderPtr &shader, QOpenGLFunctions *gl_function) {
        shader->setUniformValue("modelMatrix", transformation_);

        if (node_->node_type() == NodeType::kMeshInstance) {
            SetAttributeBuffers(shader);
            gl_function->glDrawElements(GL_TRIANGLES, (int) index_buffer_size_, GL_UNSIGNED_INT, (void *) (index_buffer_offset_ * sizeof(unsigned int)));
        }
    }

private:
    kNodePtr node_;
    QMatrix4x4 transformation_;
    size_t vertex_buffer_offset_;
    size_t index_buffer_offset_;
    size_t index_buffer_size_;

    void SetAttributeBuffers(const ShaderPtr &shader) const {
        if (node_->node_type() == NodeType::kMeshInstance) {
            kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(node_);
            kMeshPtr mesh = mesh_instance->mesh();

            shader->enableAttributeArray(VertexShaderLocation::kPosition);
            int offset = (int) (vertex_buffer_offset_ + mesh->position_offset());
            int stride = (int) mesh->vertex_size() * sizeof(float);
            shader->setAttributeBuffer(VertexShaderLocation::kPosition, GL_FLOAT, offset, VertexPropertySize::kPosition, stride);

            if (mesh->normal_offset()) {
                offset = (int) (vertex_buffer_offset_ + mesh->normal_offset());
                shader->setAttributeBuffer(VertexShaderLocation::kNormal, GL_FLOAT, offset, VertexPropertySize::kNormal, stride);
            }

            if (mesh->uv0_offset()) {
                offset = (int) (vertex_buffer_offset_ + mesh->uv0_offset());
                shader->setAttributeBuffer(VertexShaderLocation::kUV0, GL_FLOAT, offset, VertexPropertySize::kUV0, stride);
            }

            if (mesh->uv1_offset()) {
                offset = (int) (vertex_buffer_offset_ + mesh->uv1_offset());
                shader->setAttributeBuffer(VertexShaderLocation::kUV1, GL_FLOAT, offset, VertexPropertySize::kUV1, stride);
            }

            if (mesh->color_offset()) {
                offset = (int) (vertex_buffer_offset_ + mesh->color_offset());
                shader->setAttributeBuffer(VertexShaderLocation::kColor, GL_FLOAT, offset, VertexPropertySize::kColor, stride);
            }
        }
    }
};

#endif //QTSPACE_NODERENDER_H
