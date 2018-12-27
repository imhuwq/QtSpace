#include "Resource/GraphNode/Light.h"

Light::Light(const string &name,
             NodeType::Type node_type,
             LightType::Type light_type) : Node(name, node_type),
                                           light_type_(light_type),
                                           radius_(1.0f),
                                           strength_(1.0f),
                                           color_(3, 1.0f) {}