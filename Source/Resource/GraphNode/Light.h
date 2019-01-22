#ifndef QTSPACE_LIGHT_H
#define QTSPACE_LIGHT_H

#include <QColor>

#include "Node.h"

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
    Light(const string &name,
          LightType::Type light_type = LightType::kDotLight);

    QColor color() const;

    float normalized_r() const;

    float normalized_g() const;

    float normalized_b() const;

    vector<float> normalized_color() const;

    void ChangeColor(int r, int g, int b, int a = 255);

private:
    LightType::Type light_type_;
    float radius_;
    float strength_;
    QColor color_;
};

#endif //QTSPACE_LIGHT_H
