#ifndef QTSPACE_FBXFILELOADER_H
#define QTSPACE_FBXFILELOADER_H

#include <fbxsdk.h>

#include "ModelFileLoader.h"

using namespace std;

struct VertexContext {
    size_t triangle_count = 0;
    size_t controlpoint_count = 0;
    size_t triangle_index = 0;
    size_t vertex_triangle_index = 0;
    size_t vertex_index = 0;
    size_t vertex_id = 0;
    size_t buffer_index = 0;  // 最终被加入 indices buffer 的值
    vector<size_t> triangle_buffer_indices = {};  // 一个三角形的三个 buffer index
    FbxAMatrix position_offset_matrix;
};

struct VertexPack {
    VertexPack() = default;

    VertexPack(const VertexPack &pack);

    friend bool operator==(const VertexPack &lhs, const VertexPack &rhs);

    size_t index = 0;
    vector<float> positions = {};
    vector<float> normals = {};
    vector<float> uv0 = {};
    vector<float> uv1 = {};
    vector<float> colors = {};
    vector<float> tangent0 = {};
    vector<float> tangent1 = {};

    bool empty() const { return positions.empty(); }
};

inline bool operator==(const VertexPack &lhs, const VertexPack &rhs) {
    return lhs.positions == rhs.positions &&
           lhs.normals == rhs.normals &&
           lhs.uv0 == rhs.uv0 &&
           lhs.uv1 == rhs.uv1 &&
           lhs.colors == rhs.colors;
}

typedef shared_ptr<VertexPack> VertexPackPtr;
typedef shared_ptr<const VertexPack> kVertexPackPtr;

struct VertexTable {
    size_t size;
    vector<vector<kVertexPackPtr>> table;
    VertexSemanticPtr semantic;
    VertexPackPtr sample;
    bool empty;

    explicit VertexTable(size_t control_point_count) : size(control_point_count), empty(true) { table.assign(control_point_count, {}); }

    VertexSemanticPtr ParseVertexSemantic();

    bool Insert(VertexPackPtr &pack, VertexContext &context);

    void FillEmptySlots();

    kVertexSemanticPtr Flatten(vector<float> &buffer);

};

class FBXFileLoader : public ModelFileLoader {
public:
    FBXFileLoader();

    ~FBXFileLoader() override;

    ModelPtr Load(const string &file_path, NodePtr parent_node) override;

private:
    ModelPtr model_;
    NodePtr parent_node_;
    FbxManager *fbx_manager_;
    FbxScene *fbx_scene_;
    string model_file_;

    bool InitializeSDK();

    bool ImportModelFile();

    void CollectFbxMeshInstanceData(FbxNode *fbx_node, NodePtr &parent_node);

    NodePtr CollectFbxNodeData(FbxNode *fbx_node, NodePtr &parent_node);

    void WalkFbxNodeTree(FbxNode *fbx_node, NodePtr &parent_node);

    bool ParseModelFile();

    void DestroySDK();
};


#endif //QTSPACE_FBXFILELOADER_H
