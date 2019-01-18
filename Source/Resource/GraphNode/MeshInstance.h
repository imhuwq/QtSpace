#ifndef QTSPACE_MESHINSTANCE_H
#define QTSPACE_MESHINSTANCE_H

#include <vector>
#include <memory>

#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "../Mesh.h"
#include "../Material.h"
#include "Node.h"

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
                 const vector<unsigned int> &indices);

    kMeshPtr mesh() const;

    kMaterialPtr material() const;

    size_t indices_size() const;

    const vector<unsigned int> &indices() const;

private:
    kMeshPtr mesh_;
    kMaterialPtr material_;
    vector<unsigned int> indices_;
};

#endif //QTSPACE_MESHINSTANCE_H
