#ifndef QTSPACE_MATERIAL_H
#define QTSPACE_MATERIAL_H

#include <memory>
#include <string>

#include <QOpenGLShaderProgram>

#include "Resource/Resource.h"

using namespace std;

class Material;

typedef shared_ptr<Material> MaterialPtr;
typedef shared_ptr<const Material> kMaterialPtr;

class Material : public Resource {
public:
    Material(const string &name) : name_(name),
                                   ambient_color_{3, 1.0f},
                                   diffuse_color_(3, 1.0f),
                                   specular_color_(3, 1.0f),
                                   shininess_(0) {
        kTexturePtr default_texture = Texture::DEFAULT_TEXTURE();
        ambient_texture_ = default_texture;
        diffuse_texture_ = default_texture;
        specular_texture_ = default_texture;
    }

    string name() { return name_; }

    kTexturePtr ambient_texture() const { return ambient_texture_; }

    void SetAmbientTexture(const TexturePtr &ambient_texture) { ambient_texture_ = ambient_texture; }

    vector<float> ambient_color() const { return ambient_color_; }

    void SetAmbientColor(float x, float y, float z) { ambient_color_ = {x, y, z}; }

    kTexturePtr diffuse_texture() const { return diffuse_texture_; }

    void SetDiffuseTexture(const TexturePtr &diffuse_texture) { diffuse_texture_ = diffuse_texture; }

    vector<float> diffuse_color() const { return diffuse_color_; }

    void SetDiffuseColor(float x, float y, float z) { diffuse_color_ = {x, y, z}; }

    kTexturePtr specular_texture() const { return specular_texture_; }

    void SetSpecularTexture(const TexturePtr &specular_texture) { specular_texture_ = specular_texture; }

    vector<float> specular_color() const { return specular_color_; }

    void SetSpecularColor(float x, float y, float z) { specular_color_ = {x, y, z}; }

    float shininess() const { return shininess_; }

    void SetShininess(float shininess) { shininess_ = shininess; }

    vector<kTexturePtr> textures() const { return {ambient_texture_, diffuse_texture_, specular_texture_}; }

    static MaterialPtr CreateDefault() {
        MaterialPtr material = make_shared<Material>("default_material");
        TexturePtr diffuse_texture = make_shared<Texture>("default_diffuse_texture", Files::DefaultDiffuseTexturePath.toStdString());
        material->SetDiffuseTexture(diffuse_texture);
        return material;
    }

private:
    string name_;

    kTexturePtr ambient_texture_;
    vector<float> ambient_color_;

    kTexturePtr diffuse_texture_;
    vector<float> diffuse_color_;

    kTexturePtr specular_texture_;
    vector<float> specular_color_;

    float shininess_;
};

#endif //QTSPACE_MATERIAL_H
