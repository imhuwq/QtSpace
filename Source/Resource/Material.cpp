#include "Material.h"
#include "Common/Files.h"

using namespace std;

Material::Material(const string &name) : name_(name),
                                         ambient_color_(3, 1.0f),
                                         ambient_strength_(0.25f),
                                         diffuse_color_(3, 1.0f),
                                         diffuse_strength_(1.0f),
                                         specular_color_(3, 1.0f),
                                         specular_strength_(0.5f),
                                         shininess_(32.0f) {
    kTexturePtr default_texture = Texture::DEFAULT_TEXTURE();
    ambient_texture_ = default_texture;
    diffuse_texture_ = default_texture;
    specular_texture_ = default_texture;
}

string Material::name() { return name_; }

kTexturePtr Material::ambient_texture() const { return ambient_texture_; }

void Material::SetAmbientTexture(const kTexturePtr &ambient_texture) { ambient_texture_ = ambient_texture; }

vector<float> Material::ambient_color() const { return ambient_color_; }

void Material::SetAmbientColor(float x, float y, float z) { ambient_color_ = {x, y, z}; }

float Material::ambient_strength() const { return ambient_strength_; }

void Material::SetAmbientStrength(float strength) { ambient_strength_ = strength; }

kTexturePtr Material::diffuse_texture() const { return diffuse_texture_; }

void Material::SetDiffuseTexture(const kTexturePtr &diffuse_texture) { diffuse_texture_ = diffuse_texture; }

vector<float> Material::diffuse_color() const { return diffuse_color_; }

void Material::SetDiffuseColor(float x, float y, float z) { diffuse_color_ = {x, y, z}; }

float Material::diffuse_strength() const { return diffuse_strength_; }

void Material::SetDiffuseStrength(float strength) { diffuse_strength_ = strength; }

kTexturePtr Material::specular_texture() const { return specular_texture_; }

void Material::SetSpecularTexture(const kTexturePtr &specular_texture) { specular_texture_ = specular_texture; }

vector<float> Material::specular_color() const { return specular_color_; }

void Material::SetSpecularColor(float x, float y, float z) { specular_color_ = {x, y, z}; }

float Material::specular_strength() const { return diffuse_strength_; }

void Material::SetSpecularStrength(float strength) { diffuse_strength_ = strength; }

float Material::shininess() const { return shininess_; }

void Material::SetShininess(float shininess) { shininess_ = shininess; }

vector<kTexturePtr> Material::textures() const { return {ambient_texture_, diffuse_texture_, specular_texture_}; }

MaterialPtr Material::Default() {
    return make_shared<Material>("default_material");
}
