#ifndef QTSPACE_SCENERENDER_H
#define QTSPACE_SCENERENDER_H

#include <map>
#include <stack>
#include <memory>
#include <cstring>

#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "Files.h"
#include "Resource/Scene.h"
#include "GLRender/MeshInstanceRender.h"
#include "Resource/GraphNode/MeshInstance.h"

using namespace std;

typedef shared_ptr<QOpenGLBuffer> glVBOPtr;
typedef shared_ptr<QOpenGLVertexArrayObject> glVAOPtr;
typedef shared_ptr<QOpenGLTexture> glTexturePtr;

class SceneRender;

typedef shared_ptr<SceneRender> SceneRenderPtr;
typedef shared_ptr<const SceneRender> kSceneRenderPtr;


class SceneRender : protected QOpenGLFunctions {
public:
    SceneRender(kScenePtr scene) : scene_(scene),
                                   vao_(new QOpenGLVertexArrayObject()),
                                   vbo_(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
                                   ebo_(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)) {
        CreateShaderProgram();
        CreateMeshInstanceRenders();
        CreateGLBuffers();
        CreateGLTextures();
    }

    void Draw() {
        gl_functions_ = QOpenGLContext::currentContext()->functions();
        shader_->bind();
        vao_->bind();
        vbo_->bind();
        ebo_->bind();
        shader_->setUniformValue("mvpMatrix", scene_->projection() * scene_->camera().transformation() * scene_->transformation());
        RenderMeshInstances();
    }

private:
    kScenePtr scene_;
    vector<MeshInstanceRenderPtr> mesh_instance_renders_;
    size_t vbo_size_;
    size_t ebo_size_;

    glShaderPtr shader_;
    glVAOPtr vao_;
    glVBOPtr vbo_;
    glVBOPtr ebo_;
    map<string, glTexturePtr> textures_;
    QOpenGLFunctions *gl_functions_;

    void CreateShaderProgram() {
        shader_ = make_shared<QOpenGLShaderProgram>();
        shader_->addShaderFromSourceFile(QOpenGLShader::Vertex, Files::DefaultVertexShader);
        shader_->addShaderFromSourceFile(QOpenGLShader::Fragment, Files::DefaultFragmentShader);
        shader_->link();
    }

    void CreateMeshInstanceRenders(kNodePtr node, map<string, size_t> &mesh_buffer_size, QMatrix4x4 transformation) {
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

    void CreateMeshInstanceRenders() {
        vbo_size_ = 0;
        ebo_size_ = 0;
        map<string, size_t> mesh_buffer_size;

        QMatrix4x4 mvp = scene_->projection() * scene_->camera().transformation() * scene_->transformation();
        for (size_t model_index = 0; model_index < scene_->model_size(); model_index++) {
            kModelPtr model = scene_->GetModel(model_index);
            kNodePtr node = model->root_node();
            QMatrix4x4 transform = QMatrix4x4();
            transform.setToIdentity();
            CreateMeshInstanceRenders(node, mesh_buffer_size, transform);
        }
    }

    void CreateGLBuffers() {
        vao_->create();
        vbo_->create();
        ebo_->create();
        vbo_->setUsagePattern(QOpenGLBuffer::StaticDraw);
        ebo_->setUsagePattern(QOpenGLBuffer::StaticDraw);

        float vertex_buffer[vbo_size_];
        unsigned int index_buffer[ebo_size_];
        size_t vertex_buffer_offset = 0;
        size_t index_buffer_offset = 0;
        map<string, bool> mesh_buffer_loaded;

        for (const MeshInstanceRenderPtr &render:mesh_instance_renders_) {
            kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(render->node);
            kMeshPtr mesh = mesh_instance->mesh();
            string mesh_uuid = mesh->uuid();
            size_t buffer_length;
            if (mesh_buffer_loaded.find(mesh_uuid) == mesh_buffer_loaded.end()) {
                const vector<float> &mesh_vertex_buffer = mesh->vertex_buffer();
                buffer_length = mesh_vertex_buffer.size() * sizeof(float);
                memcpy(vertex_buffer + vertex_buffer_offset, mesh_vertex_buffer.data(), buffer_length);
                mesh_buffer_loaded[mesh_uuid] = true;
                vertex_buffer_offset += buffer_length;
            }

            const vector<unsigned int> &mesh_index_buffer = mesh_instance->indices();
            buffer_length = mesh_index_buffer.size() * sizeof(unsigned int);
            memcpy(index_buffer + index_buffer_offset, mesh_index_buffer.data(), buffer_length);
            index_buffer_offset += buffer_length;
        }

        vao_->bind();
        vbo_->bind();
        vbo_->allocate(vertex_buffer, (int) vbo_size_ * sizeof(float));
        ebo_->bind();
        ebo_->allocate(index_buffer, (int) ebo_size_ * sizeof(unsigned int));
    }

    void CreateGLTextures() {
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

    void PrepareGLBuffers(const kMeshInstanceRenderPtr &render) {
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

    void PrepareMaterial() {

    }

    void PrepareGLTextures(const kMeshInstanceRenderPtr &render) {
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

    void RenderMeshInstances() {
        for (const MeshInstanceRenderPtr &render:mesh_instance_renders_) {
            shader_->setUniformValue("worldMatrix", render->transformation);
            PrepareGLBuffers(render);
            PrepareMaterial();
            PrepareGLTextures(render);
            gl_functions_->glDrawElements(GL_TRIANGLES, (int) render->index_buffer_size, GL_UNSIGNED_INT, (void *) (render->index_buffer_offset * sizeof(unsigned int)));
        }
    }
};

#endif //QTSPACE_SCENERENDER_H
