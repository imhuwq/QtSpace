#ifndef QTSPACE_TEXTURE_H
#define QTSPACE_TEXTURE_H

#include <string>
#include <memory>

#include "Resource.h"

using namespace std;

class Texture;

typedef shared_ptr<Texture> TexturePtr;
typedef shared_ptr<const Texture> kTexturePtr;

class Texture : public Resource {
public:
    Texture(const string &name, const string &path);

    string name() const;

    string path() const;

    static kTexturePtr DEFAULT_TEXTURE();

private:
    string name_;
    string path_;
    static kTexturePtr default_texture_;
};

#endif //QTSPACE_TEXTURE_H
