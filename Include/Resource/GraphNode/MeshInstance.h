#ifndef QTSPACE_MESHINSTANCE_H
#define QTSPACE_MESHINSTANCE_H

#include <vector>
#include <memory>

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "Resource/GraphNode/Node.h"

using namespace std;

class Mesh;

class MeshInstance;

typedef shared_ptr<Mesh> MeshPtr;
typedef shared_ptr<const Mesh> kMeshPtr;
typedef shared_ptr<MeshInstance> MeshInstancePtr;
typedef shared_ptr<const MeshInstance> kMeshInstancePtr;


class MeshInstance : public Node {
public:
    MeshInstance(const string &name,
                 const kMeshPtr &mesh,
                 const kMaterialPtr &material,
                 const vector<unsigned int> &indices,
                 NodeType::Type node_type = NodeType::kMeshInstance) : mesh_(mesh),
                                                                       indices_(indices),
                                                                       material_(material),
                                                                       Node(name, node_type) {
        if (material == nullptr) material_ = Material::CreateDefault();
    }

    kMeshPtr mesh() const { return mesh_; }

    kMaterialPtr material() const { return material_; }

    size_t indices_size() const { return indices_.size(); }

    const vector<unsigned int> &indices() const { return indices_; }

    static MeshInstancePtr CreateDefault() {
        VertexSemantic vertex_semantic(false, true, false, false, false);
        MeshPtr mesh = make_shared<Mesh>(36, vertex_semantic);
        vector<float> vertex_buffer = {
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
        };
        mesh->SetBuffers(vertex_buffer);

        MaterialPtr material = Material::CreateDefault();
        vector<unsigned int> index_buffer = {0, 1, 2, 3, 4, 5,
                                             6, 7, 8, 9, 10, 11,
                                             12, 13, 14, 15, 16, 17,
                                             18, 19, 20, 21, 22, 23,
                                             24, 25, 26, 27, 28, 29,
                                             30, 31, 32, 33, 34, 35};

        MeshInstancePtr mesh_instance = make_shared<MeshInstance>("cube", mesh, material, index_buffer);

        return mesh_instance;
    }

private:
    kMeshPtr mesh_;
    kMaterialPtr material_;
    vector<unsigned int> indices_;
};

#endif //QTSPACE_MESHINSTANCE_H
