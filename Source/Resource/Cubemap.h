#ifndef QTSPACE_CUBEMAP_H
#define QTSPACE_CUBEMAP_H

#include "Resource.h"
#include "Common/Consts.h"
#include "Common/TypeDef.h"

class Cubemap : public Resource {
public:
	Cubemap(const std::string& front_face,
			const std::string& back_face,
			const std::string& up_face,
			const std::string& down_face,
			const std::string& left_face,
			const std::string& right_face);

	kTexturePtr front() const;

	kTexturePtr back() const;

	kTexturePtr up() const;

	kTexturePtr down() const;

	kTexturePtr left() const;

	kTexturePtr right() const;

	static CubemapPtr CreateDefault();

private:
	kTexturePtr front_;
	kTexturePtr back_;
	kTexturePtr left_;
	kTexturePtr right_;
	kTexturePtr up_;
	kTexturePtr down_;
};

#endif //QTSPACE_CUBEMAP_H
