#include "VertexSemantic.h"
#include "Common/Consts.h"

VertexSemantic::VertexSemantic(bool has_normal,
	bool has_uv0,
	bool has_uv1,
	bool has_color,
	bool has_tangent0,
	bool has_tangent1) {
	position_offset = 0;
	vertex_size += VertexPropertySize::kPosition;

	if (has_normal) {
		normal_offset = vertex_size;
		vertex_size += VertexPropertySize::kNormal;
	}
	if (has_uv0) {
		uv0_offset = vertex_size;
		vertex_size += VertexPropertySize::kUV0;
	}
	if (has_uv1) {
		uv1_offset = vertex_size;
		vertex_size += VertexPropertySize::kUV1;
	}
	if (has_color) {
		color_offset = vertex_size;
		vertex_size += VertexPropertySize::kColor;
	}
	if (has_tangent0) {
		tangent0_offset = vertex_size;
		vertex_size += VertexPropertySize::kTangent0;
	}
	if (has_tangent1) {
		tangent1_offset = vertex_size;
		vertex_size += VertexPropertySize::kTangent1;
	}
}