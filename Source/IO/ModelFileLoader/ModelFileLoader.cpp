#include "Common/Files.h"
#include "FBXFileLoader.h"
#include "ModelFileLoader.h"

ModelFileLoader::~ModelFileLoader() = default;

ModelFileLoaderPtr ModelFileLoader::CreateLoader(const string &file_ext) {
    ModelFileLoaderPtr loader = nullptr;
    if (file_ext == ModelFileType::FBX()) loader = make_shared<FBXFileLoader>();
    else if (file_ext == ModelFileType::OBJ()) loader = make_shared<FBXFileLoader>();;
    return loader;
}