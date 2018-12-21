#ifndef QTSPACE_SHADER_H
#define QTSPACE_SHADER_H

#include <QOpenGLShaderProgram>

typedef shared_ptr<QOpenGLShaderProgram> glShaderPtr;

namespace VertexAttributeLocation {
    enum Location {
        kPosition = 0,
        kNormal = 1,
        kUV0 = 2,
        kUV1 = 3,
        kColor = 4
    };
}

namespace TextureUnitLocation {
    enum Location {
        kAmbient = 0,
        kDiffuse = 1,
        kSpecular = 2
    };
}


#endif //QTSPACE_SHADER_H
