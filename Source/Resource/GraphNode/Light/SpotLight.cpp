#include "SpotLight.h"

using namespace std;

SpotLight::SpotLight(const string &name,
                     float angle,
                     float distance) : angle_(angle),
                                       distance_(distance),
                                       Light(name, LightType::kSpotLight) {}

float SpotLight::angle() const { return angle_; }

void SpotLight::SetAngle(float angle) { angle_ = angle; }

float SpotLight::distance() const { return distance_; }

void SpotLight::SetDistance(float distance) { distance_ = distance; }