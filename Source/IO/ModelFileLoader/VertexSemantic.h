#ifndef QTSPACE_VERTEXSEMANTIC_H
#define QTSPACE_VERTEXSEMANTIC_H

#include "Common/TypeDef.h"

class VertexSemantic {
public:
    VertexSemantic(bool has_normal,
                   bool has_uv0,
                   bool has_uv1,
                   bool has_color,
                   bool has_tangent0,
                   bool has_tangent1);

    size_t vertex_size = 0;
    size_t position_offset = 0;
    size_t normal_offset = 0;
    size_t uv0_offset = 0;
    size_t uv1_offset = 0;
    size_t color_offset = 0;
    size_t tangent0_offset = 0;
    size_t tangent1_offset = 0;
};


#endif // QTSPACE_VERTEXSEMANTIC_H