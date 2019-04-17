#ifndef QTSPACE_TEXTURE_H
#define QTSPACE_TEXTURE_H

#include <string>

#include "Resource.h"
#include "Common/TypeDef.h"

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
