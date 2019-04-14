#ifndef QTSPACE_MODELFILELOADER_H
#define QTSPACE_MODELFILELOADER_H

#include <memory>
#include <iostream>

#include "Resource/Model.h"

using namespace std;

class ModelFileLoader;

typedef shared_ptr<ModelFileLoader> ModelFileLoaderPtr;
typedef shared_ptr<const ModelFileLoader> kModelFileLoaderPtr;

struct ModelFileType {
    ModelFileType() = delete;

    static string OBJ() {
        const static string ext = ".obj";
        return ext;
    }

    static string FBX() {
        const static string ext = ".fbx";
        return ext;
    }
};

class ModelFileLoader {
public:
    virtual ~ModelFileLoader();

    static ModelFileLoaderPtr CreateLoader(const string &file_path);

    virtual ModelPtr Load(const string &file_path, NodePtr parent_node) = 0;
};

#endif //QTSPACE_MODELFILELOADER_H
