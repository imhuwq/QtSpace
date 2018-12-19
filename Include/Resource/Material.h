#ifndef QTSPACE_MATERIAL_H
#define QTSPACE_MATERIAL_H

#include <memory>

#include <QOpenGLShaderProgram>

#include "Resource/Resource.h"

using namespace std;

class Material;

typedef shared_ptr<Material> MaterialPtr;
typedef shared_ptr<const Material> kMaterialPtr;

class Material : public Resource {
public:
    void Bind() const {}
};

#endif //QTSPACE_MATERIAL_H
