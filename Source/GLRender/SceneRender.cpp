#include "SceneRender.h"

SceneRender::SceneRender(kScenePtr scene) : scene_(scene),
                                            vao_(new QOpenGLVertexArrayObject()),
                                            vbo_(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
                                            ebo_(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)) {
    CreateShaderProgram();
    CreateMeshInstanceRenders();
    CreateBuffers();
    CreateTextures();
}

void SceneRender::Render(kStatePtr state, QOpenGLFunctionsPtr gl_functions) {
    gl_functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    PrepareGLBuffers(gl_functions);
    PrepareGLShaderPrograms(gl_functions);
    RenderMeshInstances(gl_functions);
}

void SceneRender::CreateShaderProgram() {
    shader_ = make_shared<QOpenGLShaderProgram>();
    shader_->addShaderFromSourceFile(QOpenGLShader::Vertex, QString(Files::DefaultVertexShader.c_str()));
    shader_->addShaderFromSourceFile(QOpenGLShader::Fragment, QString(Files::DefaultFragmentShader.c_str()));
    shader_->link();
}

void SceneRender::CreateMeshInstanceRenders(kNodePtr node, map<string, size_t> &mesh_buffer_size, QMatrix4x4 transformation) {
    transformation = transformation * node->transformation();

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
    for (auto child_node: node->nodes()) CreateMeshInstanceRenders(child_node, mesh_buffer_size, transformation);
}

void SceneRender::CreateMeshInstanceRenders() {
    vbo_size_ = 0;
    ebo_size_ = 0;
    map<string, size_t> mesh_buffer_size;

    for (kNodePtr &node: scene_->nodes()) {
        QMatrix4x4 transform = QMatrix4x4();
        transform.setToIdentity();
        CreateMeshInstanceRenders(node, mesh_buffer_size, transform);
    }
}

void SceneRender::CreateBuffers() {
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

void SceneRender::CreateTextures() {
    for (const auto &render:mesh_instance_renders_) {
        kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(render->node);
        kMaterialPtr material = mesh_instance->material();
        for (const auto &texture:material->textures()) {
            if (textures_.find(texture->uuid()) == textures_.end()) {
                QOpenGLTexturePtr gl_texture = make_shared<QOpenGLTexture>(QImage(texture->path().c_str()).mirrored());
                gl_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
                gl_texture->setMagnificationFilter(QOpenGLTexture::Linear);
                textures_[texture->uuid()] = gl_texture;
            }
        }
    }
}

void SceneRender::PrepareGLBuffers(QOpenGLFunctionsPtr gl_functions) {
    shader_->bind();
    vao_->bind();
    vbo_->bind();
    ebo_->bind();
}

void SceneRender::PrepareGLShaderPrograms(QOpenGLFunctionsPtr gl_functions) {
    shader_->setUniformValue("u_vp_matrix", scene_->projection() * scene_->camera()->transformation() * scene_->transformation());

    const kLightPtr light = scene_->light();
    vector<float> color = light->color();
    QVector3D position = light->translation();
    shader_->setUniformValue("u_global_light.color", color[0], color[1], color[2]);
    shader_->setUniformValue("u_global_light.strength", light->strength());
    shader_->setUniformValue("u_global_light.position", position[0], position[1], position[2]);

    const kCameraPtr camera = scene_->camera();
    position = camera->translation();
    shader_->setUniformValue("u_camera_position", position[0], position[1], position[2]);
}

void SceneRender::PrepareBuffers(const kMeshInstanceRenderPtr &render) {
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
        shader_->setUniformValue("u_vertex_color", true);
    } else {
        shader_->setUniformValue("u_vertex_color", false);
    }
}

void SceneRender::PrepareMaterials(const kMeshInstanceRenderPtr &render) {
    kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(render->node);
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

void SceneRender::RenderMeshInstances(QOpenGLFunctionsPtr gl_functions) {

    for (const MeshInstanceRenderPtr &render:mesh_instance_renders_) {
        shader_->setUniformValue("u_model_matrix", render->transformation);
        PrepareBuffers(render);
        PrepareMaterials(render);
        gl_functions->glDrawElements(GL_TRIANGLES, (int) render->index_buffer_size, GL_UNSIGNED_INT, (void *) (render->index_buffer_offset * sizeof(unsigned int)));
    }
}