#include "Light.h"

Light::Light(const string &name,
             LightType::Type light_type) : Node(name, NodeType::kLight),
                                           light_type_(light_type),
                                           radius_(1.0f),
                                           strength_(1.0f),
                                           color_(3, 1.0f) {}