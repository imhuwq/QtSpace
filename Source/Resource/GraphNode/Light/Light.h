#ifndef QTSPACE_LIGHT_H
#define QTSPACE_LIGHT_H

#include <QColor>

#include "Resource/GraphNode/Node.h"

namespace LightType {
    enum Type {
        kGeneralLight = 0,
        kDotLight,
        kSpotLight,
        kDirectionLight,
        kNumLightType
    };
}

class Light : public Node {
public:
    Light(const string &name, LightType::Type light_type);

    LightType::Type light_type() const;

    vector<float> color() const;

    void SetColor(float r, float g, float b);

    float strength() const;

    void SetStrength(float strength);

    virtual ~Light() = 0;

protected:
    LightType::Type light_type_;
    vector<float> color_;
    float strength_;
};

typedef shared_ptr<Light> LightPtr;
typedef shared_ptr<const Light> kLightPtr;

#endif //QTSPACE_LIGHT_H
