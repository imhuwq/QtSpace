#include "DotLight.h"

DotLight::DotLight(const string &name,
                   float radius) : radius_(radius),
                                   Light(name, LightType::kDotLight) {}

float DotLight::radius() const { return radius_; }

void DotLight::SetRadius(float radius) { radius_ = radius; }