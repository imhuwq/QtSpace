#include "Texture.h"
#include "Common/Files.h"

using namespace std;

kTexturePtr Texture::default_texture_;

Texture::Texture(const string &name, const string &path) : name_(name),
                                                           path_(path) {}

string Texture::name() const { return name_; }

string Texture::path() const { return path_; }

kTexturePtr Texture::Create_Default() {
    if (!default_texture_) default_texture_ = make_shared<Texture>("default_texture", Files::TexturePath);
    return default_texture_;
}