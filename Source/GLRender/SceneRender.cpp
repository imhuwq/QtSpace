#include "SceneRender.h"

using namespace std;

SceneRender::SceneRender(kScenePtr scene) : scene_(scene),
                                            vao_(new QOpenGLVertexArrayObject()),
                                            vbo_(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
                                            ebo_(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)) {
    CreateMeshInstanceShader();
    CreateMeshInstanceRenders();
    CreateMeshInstanceBuffers();
    CreateMeshInstanceTextures();
}

void SceneRender::CreateMeshInstanceShader() {
    mesh_instance_shader_ = make_shared<QOpenGLShaderProgram>();
    mesh_instance_shader_->addShaderFromSourceFile(QOpenGLShader::Vertex, QString(Files::DefaultVertexShader.c_str()));
    mesh_instance_shader_->addShaderFromSourceFile(QOpenGLShader::Fragment, QString(Files::DefaultFragmentShader.c_str()));
    mesh_instance_shader_->link();
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
																					 mesh_instance_shader_);
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

    for (const MeshInstanceRenderPtr &render:mesh_instance_renders_) {
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

    for (const auto &render:mesh_instance_renders_) {
        kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(render->node());
        kMaterialPtr material = mesh_instance->material();
        for (const auto &texture:material->textures()) {
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

void SceneRender::CreateCubemaps() {

}

void SceneRender::PrepareMeshInstanceShader(QGLFunctionsPtr gl_functions) {
	mesh_instance_shader_->bind();

	mesh_instance_shader_->setUniformValue("u_vp_matrix", scene_->projection() * scene_->camera()->transformation() * scene_->transformation());

	const kLightPtr light = scene_->light();
	vector<float> color = light->color();
	QVector3D position = light->translation();
	mesh_instance_shader_->setUniformValue("u_global_light.color", color[0], color[1], color[2]);
	mesh_instance_shader_->setUniformValue("u_global_light.strength", light->strength());
	mesh_instance_shader_->setUniformValue("u_global_light.position", position[0], position[1], position[2]);

	const kCameraPtr camera = scene_->camera();
	position = camera->translation();
	mesh_instance_shader_->setUniformValue("u_camera_position", position[0], position[1], position[2]);
}

void SceneRender::PrepareMeshInstanceBuffers(QGLFunctionsPtr gl_functions) {
    vao_->bind();
    vbo_->bind();
    ebo_->bind();
}

void SceneRender::RenderMeshInstances(QGLFunctionsPtr gl_functions) {
	PrepareMeshInstanceShader(gl_functions);
	PrepareMeshInstanceBuffers(gl_functions);
    for (const auto &render:mesh_instance_renders_) render->Render(gl_functions);
}

void SceneRender::Render(kStatePtr state, QGLFunctionsPtr gl_functions) {
	gl_functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	RenderMeshInstances(gl_functions);
}
