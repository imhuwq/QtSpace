#include "Model.h"

Model::Model() : root_node_(make_shared<Node>("root")) {};

void Model::SetRootNode(NodePtr &root_node) { root_node_ = root_node; }

kNodePtr Model::root_node() const { return root_node_; }

NodePtr Model::root_node() { return root_node_; }

void Model::AddMesh(const MeshPtr &mesh) { meshes_.push_back(mesh); }

void Model::AddMaterial(const MaterialPtr &material) {
    materials_[material->uuid()] = material;
    if (material->ambient_texture()) textures_[material->ambient_texture()->uuid()] = material->ambient_texture();
    if (material->diffuse_texture()) textures_[material->diffuse_texture()->uuid()] = material->diffuse_texture();
    if (material->specular_texture()) textures_[material->specular_texture()->uuid()] = material->specular_texture();
}
