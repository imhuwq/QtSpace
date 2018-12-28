#include <iostream>

#include "FBXFileLoader.h"

FBXFileLoader::FBXFileLoader() : model_(nullptr),
                                 fbx_manager_(nullptr),
                                 fbx_scene_(nullptr),
                                 model_file_("") {};

FBXFileLoader::~FBXFileLoader() = default;

kModelPtr FBXFileLoader::Load(const string &file_path) {
    model_file_ = file_path;

    if (!InitializeSDK()) return nullptr;

    if (!ImportModelFile()) return nullptr;

    if (!ParseModelFile()) return nullptr;

    DestroySDK();

    return model_;
}

bool FBXFileLoader::InitializeSDK() {
    fbx_manager_ = FbxManager::Create();
    FbxIOSettings *ios = FbxIOSettings::Create(fbx_manager_, IOSROOT);
    fbx_manager_->SetIOSettings(ios);
    fbx_scene_ = FbxScene::Create(fbx_manager_, "fbx_scene");
    return true;
}

bool FBXFileLoader::ImportModelFile() {
    FbxImporter *fbxImporter = FbxImporter::Create(fbx_manager_, "");

    bool status = fbxImporter->Initialize(model_file_.c_str(), -1, fbx_manager_->GetIOSettings());
    if (!status) {
        fbxImporter->Destroy();
        cerr << "FBXFileLoader::ImportModelFile: Fail to initialize importer." << endl;
        return status;
    }

    status = fbxImporter->Import(fbx_scene_);
    if (!status) {
        fbxImporter->Destroy();
        cerr << "FBXFileLoader::ImportModelFile: Fail to import file '" << model_file_ << "'." << endl;
        return status;
    }

    fbxImporter->Destroy();
    return true;
}

bool FBXFileLoader::ParseModelFile() {

}

void FBXFileLoader::DestroySDK() {
    fbx_scene_->Destroy();
    fbx_manager_->Destroy();
}
