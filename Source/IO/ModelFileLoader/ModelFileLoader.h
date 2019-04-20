#ifndef QTSPACE_MODELFILELOADER_H
#define QTSPACE_MODELFILELOADER_H

#include "Common/TypeDef.h"

class ModelFileLoader {
public:
    virtual ~ModelFileLoader();

    static ModelFileLoaderPtr CreateLoader(const string &file_path);

    virtual NodePtr Load(const string &file_path) = 0;
};

#endif //QTSPACE_MODELFILELOADER_H
