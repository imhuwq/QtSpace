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

MeshInstancePtr MeshInstance::CreateCube() {
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
