#ifndef QTSPACE_DIRECTIONLIGHT_H
#define QTSPACE_DIRECTIONLIGHT_H

#include "Resource/GraphNode/Light/Light.h"

class DirectionLight : public Light {
public:
    DirectionLight(const string &name);
};

typedef shared_ptr<DirectionLight> DirectionLightPtr;
typedef shared_ptr<const DirectionLight> kDirectionLightPtr;

#endif //QTSPACE_DIRECTIONLIGHT_H
