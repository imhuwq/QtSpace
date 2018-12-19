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
                 NodeType::Type node_type = NodeType::kMeshInstance) : Node(name, node_type) {}

    kMeshPtr mesh() const { return mesh_; }

    string material_name() const { return material_name_; }

    size_t triangle_indices_size() const { return triangle_indices_.size(); }

    const vector<unsigned int> &triangle_indices() const { return triangle_indices_; }

private:
    kMeshPtr mesh_;
    string material_name_;
    vector<unsigned int> triangle_indices_;
};

#endif //QTSPACE_MESHINSTANCE_H
