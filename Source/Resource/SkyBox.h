#ifndef QTSPACE_SKYBOX_H
#define QTSPACE_SKYBOX_H

#include "Resource.h"
#include "Cubemap.h"
#include "GraphNode/Node.h"
#include "Common/TypeDef.h"

class SkyBox : public Resource {
public:
    SkyBox();

    kNodePtr box() const;

    NodePtr box();

    void SetBox(NodePtr node);

    kCubemapPtr cubemap() const;

    CubemapPtr cubemap();

    void SetCubemap(CubemapPtr cubemap);

private:
    NodePtr box_ = nullptr;
    CubemapPtr cubemap_ = nullptr;
};

#endif // QTSPACE_SKYBOX_H
