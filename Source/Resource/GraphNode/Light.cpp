#include "Light.h"

Light::Light(const string &name,
             LightType::Type light_type) : Node(name, NodeType::kLight),
                                           light_type_(light_type),
                                           radius_(1.0f),
                                           strength_(1.0f),
                                           color_(255, 255, 255) {}

QColor Light::color() const { return color_; }

vector<float> Light::normalized_color() const {
    vector<float> color = {color_.red() / 255.0f, color_.green() / 255.0f, color_.blue() / 255.0f};
    return color;
}

float Light::normalized_r() const { return color_.red() / 255.0f; }

float Light::normalized_g() const { return color_.green() / 255.0f; }

float Light::normalized_b() const { return color_.blue() / 255.0f; }

void Light::ChangeColor(int r, int g, int b, int a) { color_.setRgb(r, g, b, a); }
