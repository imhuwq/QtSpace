#ifndef QTSPACE_SCENERENDER_H
#define QTSPACE_SCENERENDER_H

#include <map>
#include <stack>
#include <memory>
#include <cstring>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "GLRender/NodeRender.h"
#include "Resource/Scene.h"
#include "Resource/GraphNode/MeshInstance.h"

using namespace std;

typedef shared_ptr<QOpenGLShaderProgram> ShaderPtr;
typedef shared_ptr<QOpenGLBuffer> VBOPtr;
typedef shared_ptr<QOpenGLVertexArrayObject> VAOPtr;

class SceneRender;

typedef shared_ptr<SceneRender> SceneRenderPtr;
typedef shared_ptr<const SceneRender> kSceneRenderPtr;


class SceneRender {
public:
    SceneRender(kScenePtr scene) : scene_(scene),
                                   vao_(new QOpenGLVertexArrayObject()),
                                   vbo_(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
                                   ebo_(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)) {
        FlattenNodeTrees();
        InitGLBuffers();
        LoadGLBuffers();
    }

    void Draw(const ShaderPtr &shader, QOpenGLFunctions *gl_function) {
        shader->bind();
        shader->setUniformValue("mvpMatrix", scene_->projection() * scene_->camera().transformation() * scene_->transformation());

        vao_->bind();
        vbo_->bind();
        ebo_->bind();

        for (const NodeRenderPtr &node_render:flatten_nodes) node_render->Draw(shader, gl_function);
    }

private:
    kScenePtr scene_;
    vector<NodeRenderPtr> flatten_nodes;
    size_t vbo_size_;
    size_t ebo_size_;
    VAOPtr vao_;

    VBOPtr vbo_;
    VBOPtr ebo_;

    void InitGLBuffers() {
        vao_->create();
        vbo_->create();
        ebo_->create();
        vbo_->setUsagePattern(QOpenGLBuffer::StaticDraw);
        ebo_->setUsagePattern(QOpenGLBuffer::StaticDraw);
    }

    void FlattenNodeTrees(kNodePtr node, map<string, size_t> &mesh_buffer_size, QMatrix4x4 transformation) {
        transformation *= node->transformation();
        if (node->node_type() == NodeType::kMeshInstance) {
            kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(node);
            kMeshPtr mesh = mesh_instance->mesh();
            string mesh_uuid = mesh->uuid();
            if (mesh_buffer_size.find(mesh_uuid) == mesh_buffer_size.end()) {
                mesh_buffer_size[mesh_uuid] = vbo_size_;
                vbo_size_ += mesh->vertex_buffer_size();
            }
            size_t index_buffer_size = mesh_instance->triangle_indices_size();
            NodeRenderPtr node_render = make_shared<NodeRender>(node, index_buffer_size, mesh_buffer_size[mesh_uuid], ebo_size_, transformation);
            ebo_size_ += index_buffer_size;

            flatten_nodes.push_back(node_render);
        }
        for (size_t child_index = 0; child_index < node->children_size(); child_index++) {
            FlattenNodeTrees(node->GetChild(child_index), mesh_buffer_size, transformation);
        }
    }

    void FlattenNodeTrees() {
        vbo_size_ = 0;
        ebo_size_ = 0;
        map<string, size_t> mesh_buffer_size;

        QMatrix4x4 mvp = scene_->projection() * scene_->camera().transformation() * scene_->transformation();
        for (size_t model_index = 0; model_index < scene_->model_size(); model_index++) {
            kModelPtr model = scene_->GetModel(model_index);
            kNodePtr node = model->root_node();
            QMatrix4x4 transform = QMatrix4x4();
            transform.setToIdentity();
            FlattenNodeTrees(node, mesh_buffer_size, transform);
        }
    }

    void LoadGLBuffers(kNodePtr node,
                       float *vertex_buffer, unsigned *index_buffer,
                       size_t &vertex_buffer_offset, size_t &index_buffer_offset,
                       map<string, bool> mesh_buffer_loaded) {
        size_t buffer_length;

        if (node->node_type() == NodeType::kMeshInstance) {
            kMeshInstancePtr mesh_instance = dynamic_pointer_cast<const MeshInstance>(node);
            kMeshPtr mesh = mesh_instance->mesh();
            string mesh_uuid = mesh->uuid();
            if (mesh_buffer_loaded.find(mesh_uuid) == mesh_buffer_loaded.end()) {
                const vector<float> &mesh_vertex_buffer = mesh->vertex_buffer();
                buffer_length = mesh_vertex_buffer.size() * sizeof(float);
                memcpy(vertex_buffer + vertex_buffer_offset, mesh_vertex_buffer.data(), buffer_length);
                mesh_buffer_loaded[mesh_uuid] = true;
                vertex_buffer_offset += buffer_length;
            }
            const vector<unsigned int> &mesh_index_buffer = mesh_instance->triangle_indices();
            buffer_length = mesh_index_buffer.size() * sizeof(unsigned int);
            memcpy(index_buffer + index_buffer_offset, mesh_index_buffer.data(), buffer_length);
            index_buffer_offset += buffer_length;
        }
        for (size_t child_index = 0; child_index < node->children_size(); child_index++) {
            LoadGLBuffers(node->GetChild(child_index), vertex_buffer, index_buffer, vertex_buffer_offset, index_buffer_offset, mesh_buffer_loaded);
        }

    }

    void LoadGLBuffers() {
        float vertex_buffer[vbo_size_];
        unsigned int index_buffer[ebo_size_];
        size_t vertex_buffer_offset = 0;
        size_t index_buffer_offset = 0;
        map<string, bool> mesh_buffer_loaded;

        for (size_t model_index = 0; model_index < scene_->model_size(); model_index++) {
            kModelPtr model = scene_->GetModel(model_index);
            kNodePtr node = model->root_node();
            LoadGLBuffers(node, vertex_buffer, index_buffer, vertex_buffer_offset, index_buffer_offset, mesh_buffer_loaded);
        }

        vao_->bind();
        vbo_->bind();
        vbo_->allocate(vertex_buffer, (int) vbo_size_ * sizeof(float));
        ebo_->bind();
        ebo_->allocate(index_buffer, (int) ebo_size_ * sizeof(unsigned int));
    }
};

#endif //QTSPACE_SCENERENDER_H
