#ifndef QTSPACE_MODELFILELOADER_H
#define QTSPACE_MODELFILELOADER_H

#include "Common/TypeDef.h"
#include "Resource/Model.h"

class ModelFileLoader {
public:
    virtual ~ModelFileLoader();

    static ModelFileLoaderPtr CreateLoader(const string &file_path);

    virtual ModelPtr Load(const string &file_path, NodePtr parent_node) = 0;
};

#endif //QTSPACE_MODELFILELOADER_H
