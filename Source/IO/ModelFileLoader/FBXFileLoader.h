#ifndef QTSPACE_FBXFILELOADER_H
#define QTSPACE_FBXFILELOADER_H

#include <fbxsdk.h>

#include "Common/TypeDef.h"
#include "ModelFileLoader.h"

class FBXFileLoader : public ModelFileLoader {
public:
    FBXFileLoader();

    ~FBXFileLoader() override;

    NodePtr Load(const std::string &file_path) override;

private:
    NodePtr root_node_;
    FbxManager *fbx_manager_;
    FbxScene *fbx_scene_;
    std::string model_file_;

    bool InitializeSDK();

    bool ImportModelFile();

    void CollectFbxMeshInstanceData(FbxNode *fbx_node, NodePtr parent);

    NodePtr CollectFbxNodeData(FbxNode *fbx_node);

    void WalkFbxNodeTree(FbxNode *fbx_node, NodePtr &parent_node);

    bool ParseModelFile();

    void DestroySDK();
};

#endif //QTSPACE_FBXFILELOADER_H
