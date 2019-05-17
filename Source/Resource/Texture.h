#ifndef QTSPACE_TEXTURE_H
#define QTSPACE_TEXTURE_H

#include <string>

#include "Resource.h"
#include "Common/TypeDef.h"

class Texture : public Resource {
public:
    Texture(const std::string &name, const std::string &path);

	std::string name() const;

	std::string path() const;

    static kTexturePtr Create_Default();

private:
	std::string name_;
	std::string path_;
    static kTexturePtr default_texture_;
};

#endif //QTSPACE_TEXTURE_H
