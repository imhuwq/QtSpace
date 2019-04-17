#ifndef QTSPACE_DOTLIGHT_H
#define QTSPACE_DOTLIGHT_H

#include "Common/TypeDef.h"
#include "Resource/GraphNode/Light/Light.h"

class DotLight : public Light {
public:
    DotLight(const string &name, float radius);

    float radius() const;

    void SetRadius(float radius);

private:
    float radius_;
};

#endif //QTSPACE_DOTLIGHT_H
