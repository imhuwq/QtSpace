#ifndef QTSPACE_MESHINSTANCE_H
#define QTSPACE_MESHINSTANCE_H

#include "Node.h"
#include "Common/TypeDef.h"
#include "Resource/Mesh.h"
#include "Resource/Material.h"

class MeshInstance : public Node {
public:
    MeshInstance(const std::string &name,
                 kMeshPtr mesh,
                 MaterialPtr material,
                 const std::vector<unsigned int> &indices);

    kMeshPtr mesh() const;

    kMaterialPtr material() const;

    MaterialPtr material();

    size_t indices_size() const;

    const std::vector<unsigned int> &indices() const;

private:
    kMeshPtr mesh_;
    MaterialPtr material_;
	std::vector<unsigned int> indices_;
};

#endif //QTSPACE_MESHINSTANCE_H
