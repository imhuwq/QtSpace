#ifndef QTSPACE_TEXTURE_H
#define QTSPACE_TEXTURE_H

#include <memory>

#include "Resource/Resource.h"

using namespace std;

class Texture;

typedef shared_ptr<Texture> TexturePtr;
typedef shared_ptr<const Texture> kTexturePtr;

class Texture : public Resource {

};

#endif //QTSPACE_TEXTURE_H
