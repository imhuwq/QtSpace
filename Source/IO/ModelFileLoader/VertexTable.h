#ifndef QTSPACE_VERTEXTABLE_H
#define QTSPACE_VERTEXTABLE_H

#include <vector>
#include "VertexPack.h"
#include "VertexContext.h"
#include "Common/TypeDef.h"

using namespace std;

class VertexTable {
public:
	size_t size;
	vector<vector<kVertexPackPtr>> table;
	VertexSemanticPtr semantic;
	VertexPackPtr sample;
	bool empty;

	explicit VertexTable(size_t control_point_count) : size(control_point_count), empty(true) { table.assign(control_point_count, {}); }

	VertexSemanticPtr ParseVertexSemantic();

	bool Insert(VertexPackPtr &pack, VertexContext &context);

	void FillEmptySlots();

	kVertexSemanticPtr Flatten(vector<float> &buffer);
};

#endif // QTSPACE_VERTEXTABLE_H
