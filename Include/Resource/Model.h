#ifndef QTSPACE_MODEL_H
#define QTSPACE_MODEL_H

#include <map>
#include <string>
#include <vector>
#include <memory>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Resource/Resource.h"
#include "Resource/GraphNode/Node.h"


using namespace std;

class Model;

typedef shared_ptr<Model> ModelPtr;
typedef shared_ptr<const Model> kModelPtr;

class Model : public Resource {
public:
    Model() : root_node_(make_shared<Node>("root")) {};

    kNodePtr root_node() const { return root_node_; }

    size_t mesh_size() const { return meshes_.size(); }

    kMeshPtr GetMesh(size_t index) const {
        if (index > meshes_.size() - 1) return nullptr;
        return meshes_[index];
    }

    const kMaterialPtr GetMaterial(const string &material_name) const {
        return materials_.at(material_name);
    }

private:
    NodePtr root_node_;
    vector<MeshPtr> meshes_;
    map<string, MaterialPtr> materials_;
    map<string, TexturePtr> textures_;
};

#endif //QTSPACE_MODEL_H
