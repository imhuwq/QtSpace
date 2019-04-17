#ifndef QTSPACE_DIRECTIONLIGHT_H
#define QTSPACE_DIRECTIONLIGHT_H

#include "Common/TypeDef.h"
#include "Resource/GraphNode/Light/Light.h"

class DirectionLight : public Light {
public:
    DirectionLight(const string &name);
};

#endif //QTSPACE_DIRECTIONLIGHT_H
