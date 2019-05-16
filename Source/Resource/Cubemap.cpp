#include "Cubemap.h"
#include "Common/Files.h"

using namespace std;

Cubemap::Cubemap(const std::string& front_face,
				 const std::string& back_face,
				 const std::string& up_face,
				 const std::string& down_face,
				 const std::string& left_face,
				 const std::string& right_face){

	front_ = make_shared<Texture>("front", front_face);
	front_ = make_shared<Texture>("back", back_face);
	front_ = make_shared<Texture>("left", left_face);
	front_ = make_shared<Texture>("right", right_face);
	front_ = make_shared<Texture>("up", up_face);
	front_ = make_shared<Texture>("down", down_face);
}

kTexturePtr Cubemap::front() const { 
	return front_; 
}

kTexturePtr Cubemap::back() const {
	return back_;
}

kTexturePtr Cubemap::up() const {
	return up_;
}

kTexturePtr Cubemap::down() const {
	return down_;
}

kTexturePtr Cubemap::left() const {
	return left_;
}

kTexturePtr Cubemap::right() const {
	return right_;
}

CubemapPtr Cubemap::CreateDefault() {
	return make_shared<Cubemap>(Files::DefaultCubemapFront,
								Files::DefaultCubemapBack,
								Files::DefaultCubemapUp,
								Files::DefaultCubemapDown,
								Files::DefaultCubemapLeft,
								Files::DefaultCubemapRight);
}
