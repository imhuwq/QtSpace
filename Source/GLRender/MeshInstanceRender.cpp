#include "MeshInstanceRender.h"

using namespace std;

MeshInstanceRender::MeshInstanceRender(kNodePtr node,
                                       size_t index_buffer_size,
                                       size_t vertex_buffer_offset,
                                       size_t index_buffer_offset,
                                       const QMatrix4x4 &transformation,
                                       QGLShaderPtr shader) :
        node_(node),
        transformation_(transformation),
        index_buffer_size_(index_buffer_size),
        vertex_buffer_offset_(vertex_buffer_offset),
        index_buffer_offset_(index_buffer_offset) {
    shader_ = shader;
}

kNodePtr MeshInstanceRender::node() const { return node_; }

void MeshInstanceRender::AddTexture(const std::string &texture_uuid, QGLTexturePtr texture) {
    textures_[texture_uuid] = texture;
}

void MeshInstanceRender::PrepareBuffer() {
    kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(node_);
    kMeshPtr mesh = mesh_instance->mesh();
    int offset = (int) (vertex_buffer_offset_ + mesh->position_offset()) * sizeof(float);
    int stride = (int) mesh->vertex_size() * sizeof(float);
    shader_->enableAttributeArray(VertexAttributeLocation::kPosition);
    shader_->setAttributeBuffer(VertexAttributeLocation::kPosition, GL_FLOAT, offset, VertexPropertySize::kPosition, stride);

    if (mesh->normal_offset()) {
        offset = (int) (vertex_buffer_offset_ + mesh->normal_offset()) * sizeof(float);
        shader_->enableAttributeArray(VertexAttributeLocation::kNormal);
        shader_->setAttributeBuffer(VertexAttributeLocation::kNormal, GL_FLOAT, offset, VertexPropertySize::kNormal, stride);
    }

    if (mesh->uv0_offset()) {
        offset = (int) (vertex_buffer_offset_ + mesh->uv0_offset()) * sizeof(float);
        shader_->enableAttributeArray(VertexAttributeLocation::kUV0);
        shader_->setAttributeBuffer(VertexAttributeLocation::kUV0, GL_FLOAT, offset, VertexPropertySize::kUV0, stride);
    }

    if (mesh->uv1_offset()) {
        offset = (int) (vertex_buffer_offset_ + mesh->uv1_offset()) * sizeof(float);
        shader_->enableAttributeArray(VertexAttributeLocation::kUV1);
        shader_->setAttributeBuffer(VertexAttributeLocation::kUV1, GL_FLOAT, offset, VertexPropertySize::kUV1, stride);
    }

    if (mesh->color_offset()) {
        offset = (int) (vertex_buffer_offset_ + mesh->color_offset()) * sizeof(float);
        shader_->enableAttributeArray(VertexAttributeLocation::kColor);
        shader_->setAttributeBuffer(VertexAttributeLocation::kColor, GL_FLOAT, offset, VertexPropertySize::kColor, stride);
        shader_->setUniformValue("u_vertex_color", true);
    } else {
        shader_->setUniformValue("u_vertex_color", false);
    }
}

void MeshInstanceRender::PrepareMaterial() {
    kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(node_);
    kMaterialPtr material = mesh_instance->material();

    kTexturePtr texture = material->ambient_texture();
    vector<float> color = material->ambient_color();
    float strength = material->ambient_strength();
    textures_[texture->uuid()]->bind(TextureUnitLocation::kAmbient);
    shader_->setUniformValue("u_material.ambient_texture", TextureUnitLocation::kAmbient);
    shader_->setUniformValue("u_material.ambient_color", color[0], color[1], color[2]);
    shader_->setUniformValue("u_material.ambient_strength", strength);

    texture = material->diffuse_texture();
    color = material->diffuse_color();
    strength = material->diffuse_strength();
    textures_[texture->uuid()]->bind(TextureUnitLocation::kDiffuse);
    shader_->setUniformValue("u_material.diffuse_texture", TextureUnitLocation::kDiffuse);
    shader_->setUniformValue("u_material.diffuse_color", color[0], color[1], color[2]);
    shader_->setUniformValue("u_material.diffuse_strength", strength);

    texture = material->specular_texture();
    color = material->specular_color();
    strength = material->specular_strength();
    textures_[texture->uuid()]->bind(TextureUnitLocation::kSpecular);
    shader_->setUniformValue("u_material.specular_texture", TextureUnitLocation::kSpecular);
    shader_->setUniformValue("u_material.specular_color", color[0], color[1], color[2]);
    shader_->setUniformValue("u_material.specular_strength", strength);

    shader_->setUniformValue("u_material.shininess", material->shininess());
}

void MeshInstanceRender::Render(QGLFunctionsPtr gl_functions) {
    shader_->setUniformValue("u_model_matrix", transformation_);
    PrepareBuffer();
    PrepareMaterial();
    gl_functions->glDrawElements(GL_TRIANGLES, index_buffer_size_, GL_UNSIGNED_INT, (void *) (index_buffer_offset_ * sizeof(unsigned int)));
}
