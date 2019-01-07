#include "MeshInstance.h"

MeshInstance::MeshInstance(const string &name,
                           const kMeshPtr &mesh,
                           const kMaterialPtr &material,
                           const vector<unsigned int> &indices,
                           NodeType::Type node_type) : mesh_(mesh),
                                                       indices_(indices),
                                                       material_(material),
                                                       Node(name, node_type) {
    if (material == nullptr) material_ = Material::CreateDefault();
}

kMeshPtr MeshInstance::mesh() const { return mesh_; }

kMaterialPtr MeshInstance::material() const { return material_; }

size_t MeshInstance::indices_size() const { return indices_.size(); }

const vector<unsigned int> &MeshInstance::indices() const { return indices_; }
