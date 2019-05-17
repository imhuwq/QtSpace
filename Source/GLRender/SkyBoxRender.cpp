#include "SkyBoxRender.h"

using namespace std;

SkyBoxRender::SkyBoxRender(kNodePtr node,
                           size_t index_buffer_size,
                           QGLShaderPtr shader) :
        node_(node),
        index_buffer_size_(index_buffer_size),
        shader_(shader) {}

kNodePtr SkyBoxRender::node() const {
    return node_;
}

kQGLTexturePtr SkyBoxRender::texture() const {
    return texture_;
}

QGLTexturePtr SkyBoxRender::texture() {
    return texture_;
}

void SkyBoxRender::SetTexture(QGLTexturePtr texture) {
    texture_ = texture;
}

void SkyBoxRender::PrepareBuffer() {
    kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(node_);
    kMeshPtr mesh = mesh_instance->mesh();
    int offset = (int) (mesh->position_offset()) * sizeof(float);
    int stride = (int) mesh->vertex_size() * sizeof(float);
    shader_->enableAttributeArray(VertexAttributeLocation::kPosition);
    shader_->setAttributeBuffer(VertexAttributeLocation::kPosition, GL_FLOAT, offset, VertexPropertySize::kPosition, stride);
}

void SkyBoxRender::PrepareCubemap() {
    texture_->bind(0);
    shader_->setUniformValue("u_skybox", 0);
}

void SkyBoxRender::Render(QGLFunctionsPtr gl_functions) {
    gl_functions->glDepthFunc(GL_LEQUAL);
    gl_functions->glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    PrepareBuffer();
    PrepareCubemap();
    gl_functions->glDrawElements(GL_TRIANGLES, index_buffer_size_, GL_UNSIGNED_INT, (void *) (0));
    gl_functions->glDepthFunc(GL_LESS);
}
