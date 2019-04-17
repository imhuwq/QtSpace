#ifndef QTSPACE_FBXFILELOADER_H
#define QTSPACE_FBXFILELOADER_H

#include <fbxsdk.h>

#include "Common/TypeDef.h"
#include "ModelFileLoader.h"

using namespace std;

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
