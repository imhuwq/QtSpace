#ifndef QTSPACE_SPOTLIGHT_H
#define QTSPACE_SPOTLIGHT_H

#include "Common/TypeDef.h"
#include "Resource/GraphNode/Light/Light.h"

class SpotLight : public Light {
public:
    SpotLight(const std::string &name, float angle, float distance);

    float angle() const;

    void SetAngle(float angle);

    float distance() const;

    void SetDistance(float distance);

private:
    float angle_;
    float distance_;
};

#endif //QTSPACE_SPOTLIGHT_H
