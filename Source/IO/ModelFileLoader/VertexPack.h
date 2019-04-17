#ifndef QTSPACE_VERTEXPACK_H
#define QTSPACE_VERTEXPACK_H

#include <vector>
#include "Common/TypeDef.h"

using namespace std;

class VertexPack {
public:
	VertexPack() = default;

	VertexPack(const VertexPack &pack);

	size_t index = 0;
	vector<float> positions = {};
	vector<float> normals = {};
	vector<float> uv0 = {};
	vector<float> uv1 = {};
	vector<float> colors = {};
	vector<float> tangent0 = {};
	vector<float> tangent1 = {};

	bool empty() const { return positions.empty(); }

	bool operator==(const VertexPack& rhs);
};

#endif // QTSPACE_VERTEXPACK_H