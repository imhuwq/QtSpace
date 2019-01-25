#ifndef QTSPACE_DOTLIGHT_H
#define QTSPACE_DOTLIGHT_H

#include "Resource/GraphNode/Light/Light.h"

class DotLight : public Light {
public:
    DotLight(const string &name, float radius);

    float radius() const;

    void SetRadius(float radius);

private:
    float radius_;
};

typedef shared_ptr<DotLight> DotLightPtr;
typedef shared_ptr<const DotLight> kDotLightPtr;

#endif //QTSPACE_DOTLIGHT_H
