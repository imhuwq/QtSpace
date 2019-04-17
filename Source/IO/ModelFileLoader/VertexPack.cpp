#include "VertexPack.h"

VertexPack::VertexPack(const VertexPack &pack) {
	positions = pack.positions;
	normals = pack.normals;
	uv0 = pack.uv0;
	uv1 = pack.uv1;
	colors = pack.colors;
	tangent0 = pack.tangent0;
	tangent1 = pack.tangent1;
}

bool VertexPack::operator== (const VertexPack& rhs) {
	return positions == rhs.positions &&
		   normals == rhs.normals &&
		   uv0 == rhs.uv0 &&
		   uv1 == rhs.uv1 &&
		   colors == rhs.colors;
}