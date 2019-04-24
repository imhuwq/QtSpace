#include "LightRender.h"
#include "Resource/GraphNode/MeshInstance.h"

using namespace std;

LightRender::LightRender(kNodePtr node,
                         size_t index_buffer_size,
                         const QMatrix4x4 &transformation,
                         QGLShaderPtr shader) :
        node_(node),
        index_buffer_size_(index_buffer_size),
        transformation_(transformation) {
    shader_ = shader;
}

kNodePtr LightRender::node() const { return node_; }

void LightRender::PrepareBuffer() {
    kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(node_);
    kMeshPtr mesh = mesh_instance->mesh();
    int offset = (int) (mesh->position_offset()) * sizeof(float);
    int stride = (int) mesh->vertex_size() * sizeof(float);
    shader_->enableAttributeArray(VertexAttributeLocation::kPosition);
    shader_->setAttributeBuffer(VertexAttributeLocation::kPosition, GL_FLOAT, offset, VertexPropertySize::kPosition, stride);

    if (mesh->normal_offset()) {
        offset = (int) (mesh->normal_offset()) * sizeof(float);
        shader_->enableAttributeArray(VertexAttributeLocation::kNormal);
        shader_->setAttributeBuffer(VertexAttributeLocation::kNormal, GL_FLOAT, offset, VertexPropertySize::kNormal, stride);
    }
}

void LightRender::Render(QGLFunctionsPtr gl_functions) {
    shader_->setUniformValue("u_model_matrix", transformation_);
    PrepareBuffer();
    gl_functions->glDrawElements(GL_TRIANGLES, index_buffer_size_, GL_UNSIGNED_INT, (void *) (0));
}
