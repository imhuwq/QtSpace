#ifndef QTSPACE_MODEL_H
#define QTSPACE_MODEL_H

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "GraphNode/Node.h"

using namespace std;

class Model;

typedef shared_ptr<Model> ModelPtr;
typedef shared_ptr<const Model> kModelPtr;

class Model : public Resource {
public:
    Model();

    void SetRootNode(NodePtr &root_node);

    kNodePtr root_node() const;

    NodePtr root_node();

    void AddMesh(const MeshPtr &mesh);

    void AddMaterial(const MaterialPtr &material);

private:
    NodePtr root_node_;
    vector<kMeshPtr> meshes_;
    map<string, kMaterialPtr> materials_;
    map<string, kTexturePtr> textures_;
};

#endif //QTSPACE_MODEL_H
