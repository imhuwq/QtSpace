#include "Light.h"

Light::Light(const string &name,
             LightType::Type light_type) : Node(name, NodeType::kLight),
                                           light_type_(light_type),
                                           color_(3, 1.0f),
                                           strength_(1.0f) {}

LightType::Type Light::light_type() const { return light_type_; }

vector<float> Light::color() const { return color_; }

void Light::SetColor(float r, float g, float b) { color_ = {r, g, b}; }

float Light::strength() const { return strength_; }

void Light::SetStrength(float strength) { strength_ = strength; }

Light::~Light() {}