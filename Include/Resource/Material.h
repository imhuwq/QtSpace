#ifndef QTSPACE_MATERIAL_H
#define QTSPACE_MATERIAL_H

#include <memory>
#include <vector>
#include <string>

#include "Resource/Resource.h"
#include "Resource/Texture.h"

using namespace std;

class Material;

typedef shared_ptr<Material> MaterialPtr;
typedef shared_ptr<const Material> kMaterialPtr;

class Material : public Resource {
public:
    Material(const string &name);

    string name();

    kTexturePtr ambient_texture() const;

    void SetAmbientTexture(const TexturePtr &ambient_texture);

    vector<float> ambient_color() const;

    void SetAmbientColor(float x, float y, float z);

    kTexturePtr diffuse_texture() const;

    void SetDiffuseTexture(const TexturePtr &diffuse_texture);

    vector<float> diffuse_color() const;

    void SetDiffuseColor(float x, float y, float z);

    kTexturePtr specular_texture() const;

    void SetSpecularTexture(const TexturePtr &specular_texture);

    vector<float> specular_color() const;

    void SetSpecularColor(float x, float y, float z);

    float shininess() const;

    void SetShininess(float shininess);

    vector<kTexturePtr> textures() const;

    static MaterialPtr CreateDefault();

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
