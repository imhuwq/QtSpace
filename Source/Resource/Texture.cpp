#include "Texture.h"
#include "Common/Files.h"

kTexturePtr Texture::default_texture_;

Texture::Texture(const string &name, const string &path) : name_(name),
                                                           path_(path) {}

string Texture::name() const { return name_; }

string Texture::path() const { return path_; }

kTexturePtr Texture::DEFAULT_TEXTURE() {
    if (!default_texture_) default_texture_ = make_shared<Texture>("default_texture", Files::DefaultTexturePath);
    return default_texture_;
}