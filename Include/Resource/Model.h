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

    NodePtr root_node() { return root_node_; }

    void AddMesh(const MeshPtr &mesh) { meshes_.push_back(mesh); }

    void AddMaterial(const MaterialPtr &material) {
        materials_[material->uuid()] = material;
        if (material->ambient_texture()) textures_[material->ambient_texture()->uuid()] = material->ambient_texture();
        if (material->diffuse_texture()) textures_[material->diffuse_texture()->uuid()] = material->diffuse_texture();
        if (material->specular_texture()) textures_[material->specular_texture()->uuid()] = material->specular_texture();
    }

private:
    NodePtr root_node_;
    vector<kMeshPtr> meshes_;
    map<string, kMaterialPtr> materials_;
    map<string, kTexturePtr> textures_;
};

#endif //QTSPACE_MODEL_H
