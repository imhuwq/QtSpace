#ifndef QTSPACE_VERTEXCONTEXT_H
#define QTSPACE_VERTEXCONTEXT_H

#include <vector>
#include <fbxsdk.h>
#include "Common/TypeDef.h"

class VertexContext {
public:
	size_t triangle_count = 0;
	size_t controlpoint_count = 0;
	size_t triangle_index = 0;
	size_t vertex_triangle_index = 0;
	size_t vertex_index = 0;
	size_t vertex_id = 0;
	size_t buffer_index = 0;  // 最终被加入 indices buffer 的值
	std::vector<size_t> triangle_buffer_indices = {};  // 一个三角形的三个 buffer index
	FbxAMatrix position_offset_matrix;
};

#endif // QTSPACE_VERTEXCONTEXT_H