#ifndef QTSPACE_LIGHTRENDER_H
#define QTSPACE_LIGHTRENDER_H

#include "Common/TypeDef.h"

class LightRender {
public:
    LightRender(kNodePtr node,
                size_t index_buffer_size,
                const QMatrix4x4 &transformation,
                QGLShaderPtr shader);

    kNodePtr node() const;

    void Render(QGLFunctionsPtr gl_functions);

private:
    kNodePtr node_;
    size_t index_buffer_size_;
    QMatrix4x4 transformation_;
    QGLShaderPtr shader_;

    void PrepareBuffer();
};

#endif // QTSPACE_LIGHTRENDER_H
