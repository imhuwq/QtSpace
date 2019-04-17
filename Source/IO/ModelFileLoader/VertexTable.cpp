#include "VertexTable.h"
#include "VertexSemantic.h"

bool VertexTable::Insert(VertexPackPtr &pack, VertexContext &context) {
	empty = false;
	sample = pack;

	vector<kVertexPackPtr> &vertices = table[context.vertex_index];

	if (vertices.empty()) {
		context.buffer_index = context.vertex_index;
		pack->index = context.buffer_index;
		vertices.push_back(pack);
		return true;
	}

	for (kVertexPackPtr &vertex : vertices) {
		if (vertex == pack) {
			context.buffer_index = vertex->index;
			return false;
		}
	}

	context.buffer_index = size++;
	pack->index = context.buffer_index;
	vertices.push_back(pack);
	return true;
}

void VertexTable::FillEmptySlots() {
	if (empty) return;

	for (auto vertices : table) {
		if (vertices.empty()) {
			vertices.emplace_back(sample);
		}
	}
}

VertexSemanticPtr VertexTable::ParseVertexSemantic() {
	if (empty) return nullptr;
	semantic = make_shared<VertexSemantic>(!sample->normals.empty(),
		!sample->uv0.empty(),
		!sample->uv1.empty(),
		!sample->colors.empty(),
		!sample->tangent0.empty(),
		!sample->tangent1.empty());
	return semantic;
}

kVertexSemanticPtr VertexTable::Flatten(vector<float> &buffer) {
	if (empty) return nullptr;
	ParseVertexSemantic();
	FillEmptySlots();

	buffer.resize(semantic->vertex_size * size);
	for (auto &vertices : table) {
		for (auto &vertex : vertices) {
			auto begin_iter = buffer.begin() + vertex->index * semantic->vertex_size;
			std::move(vertex->positions.begin(), vertex->positions.end(), begin_iter + semantic->position_offset);
			std::move(vertex->normals.begin(), vertex->normals.end(), begin_iter + semantic->normal_offset);
			std::move(vertex->uv0.begin(), vertex->uv0.end(), begin_iter + semantic->uv0_offset);
			std::move(vertex->uv1.begin(), vertex->uv1.end(), begin_iter + semantic->uv1_offset);
			std::move(vertex->colors.begin(), vertex->colors.end(), begin_iter + semantic->color_offset);
			std::move(vertex->tangent0.begin(), vertex->tangent0.end(), begin_iter + semantic->tangent0_offset);
			std::move(vertex->tangent1.begin(), vertex->tangent1.end(), begin_iter + semantic->tangent1_offset);
		}
	}

	return semantic;
}
