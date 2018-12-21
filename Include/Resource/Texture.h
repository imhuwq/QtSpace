#ifndef QTSPACE_TEXTURE_H
#define QTSPACE_TEXTURE_H

#include <string>
#include <memory>

#include "Files.h"
#include "Resource/Resource.h"

using namespace std;

class Texture;

typedef shared_ptr<Texture> TexturePtr;
typedef shared_ptr<const Texture> kTexturePtr;

class Texture : public Resource {
public:
    Texture(const string &name, const string &path) : name_(name),
                                                      path_(path) {}

    string name() const { return name_; }

    string path() const { return path_; }

    static kTexturePtr DEFAULT_TEXTURE() {
        if (!default_texture_) default_texture_ = make_shared<Texture>("default_texture", Files::DefaultTexturePath.toStdString());
        return default_texture_;
    }


private:
    string name_;
    string path_;
    static kTexturePtr default_texture_;
};

#endif //QTSPACE_TEXTURE_H
