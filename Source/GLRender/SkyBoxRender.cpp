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

void SkyBoxRender::AddTexture(const std::string &texture_uuid, QGLTexturePtr texture) {
	textures_[texture_uuid] = texture;
}

void SkyBoxRender::PrepareBuffer() {
	kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(node_);
	kMeshPtr mesh = mesh_instance->mesh();
	int offset = (int)(mesh->position_offset()) * sizeof(float);
	int stride = (int)mesh->vertex_size() * sizeof(float);
	shader_->enableAttributeArray(VertexAttributeLocation::kPosition);
	shader_->setAttributeBuffer(VertexAttributeLocation::kPosition, GL_FLOAT, offset, VertexPropertySize::kPosition, stride);
}

void SkyBoxRender::PrepareCubemap() {

}

void SkyBoxRender::Render(QGLFunctionsPtr gl_functions) {
	QMatrix4x4 transformation;
	transformation.setToIdentity();
	shader_->setUniformValue("u_model_matrix", transformation);
	PrepareBuffer();
	PrepareCubemap();
	gl_functions->glDrawElements(GL_TRIANGLES, index_buffer_size_, GL_UNSIGNED_INT, (void *)(0));
}


