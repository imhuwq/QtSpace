#ifndef QTSPACE_MATERIAL_H
#define QTSPACE_MATERIAL_H

#include <memory>
#include <vector>
#include <string>

#include "Resource.h"
#include "Texture.h"
#include "Common/TypeDef.h"

class Material : public Resource {
public:
    Material(const std::string &name);

	std::string name();

    kTexturePtr ambient_texture() const;

    void SetAmbientTexture(const kTexturePtr &ambient_texture);

	std::vector<float> ambient_color() const;

    void SetAmbientColor(float x, float y, float z);

    float ambient_strength() const;

    void SetAmbientStrength(float strength);

    kTexturePtr diffuse_texture() const;

    void SetDiffuseTexture(const kTexturePtr &diffuse_texture);

	std::vector<float> diffuse_color() const;

    void SetDiffuseColor(float x, float y, float z);

    float diffuse_strength() const;

    void SetDiffuseStrength(float strength);

    kTexturePtr specular_texture() const;

    void SetSpecularTexture(const kTexturePtr &specular_texture);

	std::vector<float> specular_color() const;

    void SetSpecularColor(float x, float y, float z);

    float specular_strength() const;

    void SetSpecularStrength(float strength);

    float shininess() const;

    void SetShininess(float shininess);

	std::vector<kTexturePtr> textures() const;

    static MaterialPtr CreateDefault();

private:
	std::string name_;

    kTexturePtr ambient_texture_;
	std::vector<float> ambient_color_;
    float ambient_strength_;

    kTexturePtr diffuse_texture_;
	std::vector<float> diffuse_color_;
    float diffuse_strength_;

    kTexturePtr specular_texture_;
	std::vector<float> specular_color_;
    float specular_strength_;

    float shininess_;
};

#endif //QTSPACE_MATERIAL_H
