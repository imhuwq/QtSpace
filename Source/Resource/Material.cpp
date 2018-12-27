#include "Resource/Material.h"
#include "Files.h"

Material::Material(const string &name) : name_(name),
                                         ambient_color_{3, 1.0f},
                                         diffuse_color_(3, 1.0f),
                                         specular_color_(3, 1.0f),
                                         shininess_(0) {
    kTexturePtr default_texture = Texture::DEFAULT_TEXTURE();
    ambient_texture_ = default_texture;
    diffuse_texture_ = default_texture;
    specular_texture_ = default_texture;
}

string Material::name() { return name_; }

kTexturePtr Material::ambient_texture() const { return ambient_texture_; }

void Material::SetAmbientTexture(const TexturePtr &ambient_texture) { ambient_texture_ = ambient_texture; }

vector<float> Material::ambient_color() const { return ambient_color_; }

void Material::SetAmbientColor(float x, float y, float z) { ambient_color_ = {x, y, z}; }

kTexturePtr Material::diffuse_texture() const { return diffuse_texture_; }

void Material::SetDiffuseTexture(const TexturePtr &diffuse_texture) { diffuse_texture_ = diffuse_texture; }

vector<float> Material::diffuse_color() const { return diffuse_color_; }

void Material::SetDiffuseColor(float x, float y, float z) { diffuse_color_ = {x, y, z}; }

kTexturePtr Material::specular_texture() const { return specular_texture_; }

void Material::SetSpecularTexture(const TexturePtr &specular_texture) { specular_texture_ = specular_texture; }

vector<float> Material::specular_color() const { return specular_color_; }

void Material::SetSpecularColor(float x, float y, float z) { specular_color_ = {x, y, z}; }

float Material::shininess() const { return shininess_; }

void Material::SetShininess(float shininess) { shininess_ = shininess; }

vector<kTexturePtr> Material::textures() const { return {ambient_texture_, diffuse_texture_, specular_texture_}; }

MaterialPtr Material::CreateDefault() {
    MaterialPtr material = make_shared<Material>("default_material");
    TexturePtr diffuse_texture = make_shared<Texture>("default_diffuse_texture", Files::DefaultDiffuseTexturePath.toStdString());
    material->SetDiffuseTexture(diffuse_texture);
    return material;
}
