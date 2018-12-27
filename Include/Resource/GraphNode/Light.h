#ifndef QTSPACE_LIGHT_H
#define QTSPACE_LIGHT_H

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
    Light(const string &name,
          NodeType::Type node_type = NodeType::kLight,
          LightType::Type light_type = LightType::kDotLight);

private:
    LightType::Type light_type_;
    float radius_;
    float strength_;
    vector<float> color_;
};

#endif //QTSPACE_LIGHT_H
