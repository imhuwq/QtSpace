#include "SceneRender.h"

SceneRender::SceneRender(kScenePtr scene) : scene_(scene),
                                            vao_(new QOpenGLVertexArrayObject()),
                                            vbo_(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
                                            ebo_(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)) {
    CreateShaderProgram();
    CreateMeshInstanceRenders();
    CreateGLBuffers();
    CreateGLTextures();
}

void SceneRender::SceneRender::Draw() {
    gl_functions_ = QOpenGLContext::currentContext()->functions();
    shader_->bind();
    vao_->bind();
    vbo_->bind();
    ebo_->bind();
    shader_->setUniformValue("mvpMatrix", scene_->projection() * scene_->camera().transformation() * scene_->transformation());
    RenderMeshInstances();
}

void SceneRender::CreateShaderProgram() {
    shader_ = make_shared<QOpenGLShaderProgram>();
    shader_->addShaderFromSourceFile(QOpenGLShader::Vertex, QString(Files::DefaultVertexShader.c_str()));
    shader_->addShaderFromSourceFile(QOpenGLShader::Fragment, QString(Files::DefaultFragmentShader.c_str()));
    shader_->link();
}

void SceneRender::CreateMeshInstanceRenders(kNodePtr node, map<string, size_t> &mesh_buffer_size, QMatrix4x4 transformation) {
    transformation *= node->transformation();
    if (node->node_type() == NodeType::kMeshInstance) {
        kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(node);
        kMeshPtr mesh = mesh_instance->mesh();
        string mesh_uuid = mesh->uuid();
        if (mesh_buffer_size.find(mesh_uuid) == mesh_buffer_size.end()) {
            mesh_buffer_size[mesh_uuid] = vbo_size_;
            vbo_size_ += mesh->vertex_buffer_size();
        }
        size_t index_buffer_size = mesh_instance->indices_size();
        MeshInstanceRenderPtr mesh_instance_render = make_shared<MeshInstanceRender>(node, index_buffer_size, mesh_buffer_size[mesh_uuid], ebo_size_, transformation);
        ebo_size_ += index_buffer_size;

        mesh_instance_renders_.push_back(mesh_instance_render);
    }
    for (size_t child_index = 0; child_index < node->children_size(); child_index++) {
        CreateMeshInstanceRenders(node->GetChild(child_index), mesh_buffer_size, transformation);
    }
}

void SceneRender::CreateMeshInstanceRenders() {
    vbo_size_ = 0;
    ebo_size_ = 0;
    map<string, size_t> mesh_buffer_size;

    for (size_t model_index = 0; model_index < scene_->model_size(); model_index++) {
        kModelPtr model = scene_->GetModel(model_index);
        kNodePtr node = model->root_node();
        QMatrix4x4 transform = QMatrix4x4();
        transform.setToIdentity();
        CreateMeshInstanceRenders(node, mesh_buffer_size, transform);
    }
}

void SceneRender::CreateGLBuffers() {
    vao_->create();
    vbo_->create();
    ebo_->create();
    vbo_->setUsagePattern(QOpenGLBuffer::StaticDraw);
    ebo_->setUsagePattern(QOpenGLBuffer::StaticDraw);

    vector<float> vertex_buffer(vbo_size_);
    vector<unsigned int> index_buffer(ebo_size_);
    size_t vertex_buffer_offset = 0;
    size_t index_buffer_offset = 0;
    map<string, bool> mesh_buffer_loaded;

    for (const MeshInstanceRenderPtr &render:mesh_instance_renders_) {
        kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(render->node);
        kMeshPtr mesh = mesh_instance->mesh();
        string mesh_uuid = mesh->uuid();
        if (mesh_buffer_loaded.find(mesh_uuid) == mesh_buffer_loaded.end()) {
            const vector<float> &mesh_vertex_buffer = mesh->vertex_buffer();
            std::copy(mesh_vertex_buffer.begin(), mesh_vertex_buffer.end(), vertex_buffer.begin() + vertex_buffer_offset);
            mesh_buffer_loaded[mesh_uuid] = true;
            vertex_buffer_offset += mesh_vertex_buffer.size();
        }

        const vector<unsigned int> &mesh_index_buffer = mesh_instance->indices();
        std::copy(mesh_index_buffer.begin(), mesh_index_buffer.end(), index_buffer.begin() + index_buffer_offset);
        index_buffer_offset += mesh_index_buffer.size();
    }

    vao_->bind();
    vbo_->bind();
    vbo_->allocate(vertex_buffer.data(), (int) vbo_size_ * sizeof(float));
    ebo_->bind();
    ebo_->allocate(index_buffer.data(), (int) ebo_size_ * sizeof(unsigned int));
}

void SceneRender::CreateGLTextures() {
    for (const auto &render:mesh_instance_renders_) {
        kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(render->node);
        kMaterialPtr material = mesh_instance->material();
        for (const auto &texture:material->textures()) {
            if (textures_.find(texture->uuid()) == textures_.end()) {
                glTexturePtr gl_texture = make_shared<QOpenGLTexture>(QImage(texture->path().c_str()).mirrored());
                gl_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
                gl_texture->setMagnificationFilter(QOpenGLTexture::Linear);
                textures_[texture->uuid()] = gl_texture;
            }
        }
    }
}

void SceneRender::PrepareGLBuffers(const kMeshInstanceRenderPtr &render) {
    kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(render->node);
    kMeshPtr mesh = mesh_instance->mesh();
    int offset = (int) (render->vertex_buffer_offset + mesh->position_offset()) * sizeof(float);
    int stride = (int) mesh->vertex_size() * sizeof(float);
    shader_->enableAttributeArray(VertexAttributeLocation::kPosition);
    shader_->setAttributeBuffer(VertexAttributeLocation::kPosition, GL_FLOAT, offset, VertexPropertySize::kPosition, stride);

    if (mesh->normal_offset()) {
        offset = (int) (render->vertex_buffer_offset + mesh->normal_offset()) * sizeof(float);
        shader_->enableAttributeArray(VertexAttributeLocation::kNormal);
        shader_->setAttributeBuffer(VertexAttributeLocation::kNormal, GL_FLOAT, offset, VertexPropertySize::kNormal, stride);
    }

    if (mesh->uv0_offset()) {
        offset = (int) (render->vertex_buffer_offset + mesh->uv0_offset()) * sizeof(float);
        shader_->enableAttributeArray(VertexAttributeLocation::kUV0);
        shader_->setAttributeBuffer(VertexAttributeLocation::kUV0, GL_FLOAT, offset, VertexPropertySize::kUV0, stride);
    }

    if (mesh->uv1_offset()) {
        offset = (int) (render->vertex_buffer_offset + mesh->uv1_offset()) * sizeof(float);
        shader_->enableAttributeArray(VertexAttributeLocation::kUV1);
        shader_->setAttributeBuffer(VertexAttributeLocation::kUV1, GL_FLOAT, offset, VertexPropertySize::kUV1, stride);
    }

    if (mesh->color_offset()) {
        offset = (int) (render->vertex_buffer_offset + mesh->color_offset()) * sizeof(float);
        shader_->enableAttributeArray(VertexAttributeLocation::kColor);
        shader_->setAttributeBuffer(VertexAttributeLocation::kColor, GL_FLOAT, offset, VertexPropertySize::kColor, stride);
    }
}

void SceneRender::PrepareMaterial() {

}

void SceneRender::PrepareGLTextures(const kMeshInstanceRenderPtr &render) {
    kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(render->node);
    kMaterialPtr material = mesh_instance->material();

    kTexturePtr texture = material->ambient_texture();
    textures_[texture->uuid()]->bind(TextureUnitLocation::kAmbient);
    shader_->setUniformValue("ambientTexture", TextureUnitLocation::kAmbient);

    texture = material->diffuse_texture();
    textures_[texture->uuid()]->bind(TextureUnitLocation::kDiffuse);
    shader_->setUniformValue("diffuseTexture", TextureUnitLocation::kDiffuse);

    texture = material->specular_texture();
    textures_[texture->uuid()]->bind(TextureUnitLocation::kSpecular);
    shader_->setUniformValue("specularTexture", TextureUnitLocation::kSpecular);
}

void SceneRender::RenderMeshInstances() {
    for (const MeshInstanceRenderPtr &render:mesh_instance_renders_) {
        shader_->setUniformValue("worldMatrix", render->transformation);
        PrepareGLBuffers(render);
        PrepareMaterial();
        PrepareGLTextures(render);
        gl_functions_->glDrawElements(GL_TRIANGLES, (int) render->index_buffer_size, GL_UNSIGNED_INT, (void *) (render->index_buffer_offset * sizeof(unsigned int)));
    }
}