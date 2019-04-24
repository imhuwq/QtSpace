#include "MeshInstance.h"

using namespace std;

MeshInstance::MeshInstance(const string &name,
                           kMeshPtr mesh,
                           MaterialPtr material,
                           const vector<unsigned int> &indices) : Node(name, NodeType::kMeshInstance),
                                                                  mesh_(mesh),
                                                                  indices_(indices),
                                                                  material_(material) {
    if (material == nullptr) material_ = Material::CreateDefault();
}

kMeshPtr MeshInstance::mesh() const { return mesh_; }

kMaterialPtr MeshInstance::material() const { return material_; }

MaterialPtr MeshInstance::material() { return material_; }

size_t MeshInstance::indices_size() const { return indices_.size(); }

const vector<unsigned int> &MeshInstance::indices() const { return indices_; }
