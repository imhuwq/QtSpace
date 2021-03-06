#include "SceneRender.h"

using namespace std;

SceneRender::SceneRender(kScenePtr scene) : scene_(scene),
                                            vao_(new QOpenGLVertexArrayObject()),
                                            vbo_(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
                                            ebo_(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)),
                                            light_vao_(new QOpenGLVertexArrayObject()),
                                            light_vbo_(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
                                            light_ebo_(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)),
                                            skybox_vao_(new QOpenGLVertexArrayObject()),
                                            skybox_vbo_(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
                                            skybox_ebo_(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)) {
    // Init Light Render
    CreateLightShader();
    CreateLightRender();
    CreateLightBuffer();

    // Init Skybox Render
    CreateSkyboxShaders();
    CreateSkyboxRender();
    CreateSkyboxBuffer();
    CreateSkyboxTexture();

    // Init MeshInstance Renders
    CreateMeshInstanceShaders();
    CreateMeshInstanceRenders();
    CreateMeshInstanceBuffers();
    CreateMeshInstanceTextures();
}

void SceneRender::CreateLightShader() {
    light_shader_ = make_shared<QOpenGLShaderProgram>();
    light_shader_->addShaderFromSourceFile(QOpenGLShader::Vertex, QString(Files::LightVertexShader.c_str()));
    light_shader_->addShaderFromSourceFile(QOpenGLShader::Fragment, QString(Files::LightFragmentShader.c_str()));
    light_shader_->link();
}

void SceneRender::CreateLightRender() {
    light_vbo_size_ = 0;
    light_ebo_size_ = 0;
    map<string, size_t> mesh_buffer_size;

    kNodePtr node = scene_->light_->nodes()[0];

    QMatrix4x4 transform = scene_->light()->transformation();
    transform = transform * node->transformation();

    kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(node);
    kMeshPtr mesh = mesh_instance->mesh();
    light_vbo_size_ = mesh->vertex_buffer_size();
    light_ebo_size_ = mesh_instance->indices_size();
    light_render_ = make_shared<LightRender>(node, light_ebo_size_, transform, light_shader_);
}

void SceneRender::CreateLightBuffer() {
    light_vao_->create();
    light_vbo_->create();
    light_ebo_->create();
    light_vbo_->setUsagePattern(QOpenGLBuffer::StaticDraw);
    light_ebo_->setUsagePattern(QOpenGLBuffer::StaticDraw);

    kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(light_render_->node());
    kMeshPtr mesh = mesh_instance->mesh();
    const vector<float> &mesh_vertex_buffer = mesh->vertex_buffer();
    const vector<unsigned int> &mesh_index_buffer = mesh_instance->indices();

    light_vao_->bind();
    light_vbo_->bind();
    light_vbo_->allocate(mesh_vertex_buffer.data(), (int) light_vbo_size_ * sizeof(float));
    light_ebo_->bind();
    light_ebo_->allocate(mesh_index_buffer.data(), (int) light_ebo_size_ * sizeof(unsigned int));
}

void SceneRender::PrepareLightShader(QGLFunctionsPtr gl_functions) {
    light_shader_->bind();

    light_shader_->setUniformValue("u_vp_matrix", scene_->projection() * scene_->camera()->transformation() * scene_->transformation());

    const kLightPtr light = scene_->light();
    vector<float> color = light->color();
    QVector3D position = light->translation();
    light_shader_->setUniformValue("u_light_color", color[0], color[1], color[2]);
    light_shader_->setUniformValue("u_light_strength", light->strength());
    light_shader_->setUniformValue("u_light_position", position[0], position[1], position[2]);

    const kCameraPtr camera = scene_->camera();
    position = camera->translation();
    light_shader_->setUniformValue("u_camera_position", position[0], position[1], position[2]);
}

void SceneRender::PrepareLightBuffer(QGLFunctionsPtr gl_functions) {
    light_vao_->bind();
    light_vbo_->bind();
    light_ebo_->bind();
}

void SceneRender::RenderLight(QGLFunctionsPtr gl_functions) {
    PrepareLightShader(gl_functions);
    PrepareLightBuffer(gl_functions);
    light_render_->Render(gl_functions);
}

void SceneRender::CreateSkyboxShaders() {
    skybox_shader_ = make_shared<QOpenGLShaderProgram>();
    skybox_shader_->addShaderFromSourceFile(QOpenGLShader::Vertex, QString(Files::SkyboxVertexShader.c_str()));
    skybox_shader_->addShaderFromSourceFile(QOpenGLShader::Fragment, QString(Files::SkyboxFragmentShader.c_str()));
    skybox_shader_->link();
}

void SceneRender::CreateSkyboxRender() {
    skybox_vbo_size_ = 0;
    skybox_ebo_size_ = 0;
    map<string, size_t> mesh_buffer_size;

    kNodePtr node = scene_->skybox_->box();
    kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(node);
    kMeshPtr mesh = mesh_instance->mesh();
    skybox_vbo_size_ = mesh->vertex_buffer_size();
    skybox_ebo_size_ = mesh_instance->indices_size();
    skybox_render_ = make_shared<SkyBoxRender>(node, skybox_ebo_size_, skybox_shader_);
}

void SceneRender::CreateSkyboxBuffer() {
    skybox_vao_->create();
    skybox_vbo_->create();
    skybox_ebo_->create();
    skybox_vbo_->setUsagePattern(QOpenGLBuffer::StaticDraw);
    skybox_ebo_->setUsagePattern(QOpenGLBuffer::StaticDraw);

    kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(skybox_render_->node());
    kMeshPtr mesh = mesh_instance->mesh();
    const vector<float> &mesh_vertex_buffer = mesh->vertex_buffer();
    const vector<unsigned int> &mesh_index_buffer = mesh_instance->indices();

    skybox_vao_->bind();
    skybox_vbo_->bind();
    skybox_vbo_->allocate(mesh_vertex_buffer.data(), (int) skybox_vbo_size_ * sizeof(float));
    skybox_ebo_->bind();
    skybox_ebo_->allocate(mesh_index_buffer.data(), (int) skybox_ebo_size_ * sizeof(unsigned int));
}

void SceneRender::CreateSkyboxTexture() {
    kTexturePtr texture;
    kCubemapPtr cubemap = scene_->skybox_->cubemap();
    QOpenGLTexture::CubeMapFace position = QOpenGLTexture::CubeMapNegativeX;

    QGLTexturePtr gl_texture = make_shared<QOpenGLTexture>(QOpenGLTexture::TargetCubeMap);
    gl_texture->create();
    QImage image = QImage(cubemap->front()->path().c_str());
    gl_texture->setSize(image.width(), image.height(), image.depth());
    gl_texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
    gl_texture->allocateStorage();

    for (int location = 0; location < CubemapLocation::kNumCubemapLocation; location++) {
        switch (location) {
            case CubemapLocation::kFront:
                texture = cubemap->front();
                position = QOpenGLTexture::CubeMapPositiveZ;
                break;
            case CubemapLocation::kBack:
                texture = cubemap->back();
                position = QOpenGLTexture::CubeMapNegativeZ;
                break;
            case CubemapLocation::kLeft:
                texture = cubemap->left();
                position = QOpenGLTexture::CubeMapNegativeX;
                break;
            case CubemapLocation::kRight:
                texture = cubemap->right();
                position = QOpenGLTexture::CubeMapPositiveX;
                break;
            case CubemapLocation::kUp:
                texture = cubemap->up();
                position = QOpenGLTexture::CubeMapPositiveY;
                break;
            case CubemapLocation::kDown:
                texture = cubemap->down();
                position = QOpenGLTexture::CubeMapNegativeY;
                break;
        }

        image = QImage(texture->path().c_str()).convertToFormat(QImage::Format_RGBA8888);
        gl_texture->setData(0, 0, position, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, (const void *) image.constBits(), 0);
    }

    gl_texture->generateMipMaps();
    gl_texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    gl_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    gl_texture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
    skybox_render_->SetTexture(gl_texture);

    textures_[texture->uuid()] = gl_texture;
}

void SceneRender::PrepareSkyboxShader(QGLFunctionsPtr gl_functions) {
    static QMatrix4x4 initial_projection;
    static bool projection_inited = false;

    if (!projection_inited) {
        initial_projection = scene_->projection();
        projection_inited = true;
    }

    skybox_shader_->bind();
    QMatrix4x4 view_matrix = scene_->camera()->transformation();
    QVector4D identity_vec4(0, 0, 0, 1);
    view_matrix.setRow(3, identity_vec4);
    view_matrix.setColumn(3, identity_vec4);

    skybox_shader_->setUniformValue("u_vp_matrix", initial_projection * view_matrix);
    skybox_shader_->setUniformValue("u_model_matrix", skybox_render_->node()->transformation());
}

void SceneRender::PrepareSkyboxBuffer(QGLFunctionsPtr gl_functions) {
    skybox_vao_->bind();
    skybox_vbo_->bind();
    skybox_ebo_->bind();
}

void SceneRender::RenderSkybox(QGLFunctionsPtr gl_functions) {
    PrepareSkyboxShader(gl_functions);
    PrepareSkyboxBuffer(gl_functions);
    skybox_render_->Render(gl_functions);
}

void SceneRender::CreateMeshInstanceShaders() {
    mi_shader_ = make_shared<QOpenGLShaderProgram>();
    mi_shader_->addShaderFromSourceFile(QOpenGLShader::Vertex, QString(Files::ObjectVertexShader.c_str()));
    mi_shader_->addShaderFromSourceFile(QOpenGLShader::Fragment, QString(Files::ObjectFragmentShader.c_str()));
    mi_shader_->link();
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
        MeshInstanceRenderPtr mesh_instance_render = make_shared<MeshInstanceRender>(node, index_buffer_size,
                                                                                     mesh_buffer_size[mesh_uuid],
                                                                                     ebo_size_, transformation,
                                                                                     mi_shader_);
        ebo_size_ += index_buffer_size;

        mesh_instance_renders_.push_back(mesh_instance_render);
    }

    for (auto child_node : node->nodes()) CreateMeshInstanceRenders(child_node, mesh_buffer_size, transformation);
}

void SceneRender::CreateMeshInstanceRenders() {
    vbo_size_ = 0;
    ebo_size_ = 0;
    map<string, size_t> mesh_buffer_size;

    for (kNodePtr &node : scene_->nodes()) {
        QMatrix4x4 transform = QMatrix4x4();
        transform.setToIdentity();
        CreateMeshInstanceRenders(node, mesh_buffer_size, transform);
    }
}

void SceneRender::CreateMeshInstanceBuffers() {
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

    for (const MeshInstanceRenderPtr &render : mesh_instance_renders_) {
        kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(render->node());
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

void SceneRender::CreateMeshInstanceTextures() {
    map<string, QGLTexturePtr> textures;

    for (const auto &render : mesh_instance_renders_) {
        kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(render->node());
        kMaterialPtr material = mesh_instance->material();
        for (const auto &texture : material->textures()) {
            if (textures.find(texture->uuid()) == textures.end()) {
                QGLTexturePtr gl_texture = make_shared<QOpenGLTexture>(QImage(texture->path().c_str()).mirrored());
                gl_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
                gl_texture->setMagnificationFilter(QOpenGLTexture::Linear);
                textures[texture->uuid()] = gl_texture;
            }

            QGLTexturePtr gl_texture = textures[texture->uuid()];
            render->AddTexture(texture->uuid(), gl_texture);
        }
    }

    for (auto &pair : textures) textures_[pair.first] = pair.second;
}

void SceneRender::PrepareMeshInstanceShader(QGLFunctionsPtr gl_functions) {
    mi_shader_->bind();

    mi_shader_->setUniformValue("u_vp_matrix", scene_->projection() * scene_->camera()->transformation() * scene_->transformation());

    const kLightPtr light = scene_->light();
    vector<float> color = light->color();
    QVector3D position = light->translation();
    mi_shader_->setUniformValue("u_global_light.color", color[0], color[1], color[2]);
    mi_shader_->setUniformValue("u_global_light.strength", light->strength());
    mi_shader_->setUniformValue("u_global_light.position", position[0], position[1], position[2]);

    QGLTexturePtr cubemap_texture = skybox_render_->texture();
    cubemap_texture->bind(TextureUnitLocation::kCubemap);
    mi_shader_->setUniformValue("u_skybox", TextureUnitLocation::kCubemap);

    const kCameraPtr camera = scene_->camera();
    position = camera->translation();
    mi_shader_->setUniformValue("u_camera_position", position[0], position[1], position[2]);
}

void SceneRender::PrepareMeshInstanceBuffers(QGLFunctionsPtr gl_functions) {
    vao_->bind();
    vbo_->bind();
    ebo_->bind();
}

void SceneRender::RenderMeshInstances(QGLFunctionsPtr gl_functions) {
    PrepareMeshInstanceShader(gl_functions);
    PrepareMeshInstanceBuffers(gl_functions);
    for (const auto &render : mesh_instance_renders_) render->Render(gl_functions);
}

void SceneRender::Render(kStatePtr state, QGLFunctionsPtr gl_functions) {
    gl_functions->glEnable(GL_DEPTH_TEST);
    gl_functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl_functions->glClearColor(0, 0, 0, 0);

    gl_functions->glDisable(GL_CULL_FACE);
    RenderSkybox(gl_functions);

    gl_functions->glEnable(GL_CULL_FACE);
    RenderLight(gl_functions);
    RenderMeshInstances(gl_functions);
}
