#ifndef QTSPACE_FBXFILELOADER_H
#define QTSPACE_FBXFILELOADER_H

#include <fbxsdk.h>

#include "ModelFileLoader.h"

using namespace std;

class FBXFileLoader : public ModelFileLoader {
public:
    FBXFileLoader();

    ~FBXFileLoader() override;

    kModelPtr Load(const string &file_path) override;

private:
    ModelPtr model_;
    FbxManager *fbx_manager_;
    FbxScene *fbx_scene_;
    string model_file_;

    bool InitializeSDK();

    bool ImportModelFile();

    bool ParseModelFile();

    void DestroySDK();
};


#endif //QTSPACE_FBXFILELOADER_H
