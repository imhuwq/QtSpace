#ifndef QTSPACE_VERTEXPACK_H
#define QTSPACE_VERTEXPACK_H

#include <vector>
#include "Common/TypeDef.h"

class VertexPack {
public:
	VertexPack() = default;

	VertexPack(const VertexPack &pack);

	size_t index = 0;
	std::vector<float> positions = {};
	std::vector<float> normals = {};
	std::vector<float> uv0 = {};
	std::vector<float> uv1 = {};
	std::vector<float> colors = {};
	std::vector<float> tangent0 = {};
	std::vector<float> tangent1 = {};

	bool empty() const { return positions.empty(); }

	bool operator==(const VertexPack& rhs);
};

#endif // QTSPACE_VERTEXPACK_H