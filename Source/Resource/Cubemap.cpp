#include "Cubemap.h"
#include "Common/Files.h"

using namespace std;

Cubemap::Cubemap(const std::string& front_face,
				 const std::string& back_face,
				 const std::string& up_face,
				 const std::string& down_face,
				 const std::string& left_face,
				 const std::string& right_face): faces_(CubemapFace::kNumFace, "") {
	faces_[CubemapFace::kFront] = front_face;
	faces_[CubemapFace::kBack] = back_face;
	faces_[CubemapFace::kUp] = up_face;
	faces_[CubemapFace::kDown] = down_face;
	faces_[CubemapFace::kLeft] = left_face;
	faces_[CubemapFace::kRight] = right_face;
}

string Cubemap::front_face_path() const { 
	return faces_[CubemapFace::kFront]; 
}

void Cubemap::SetFrontFacePath(const std::string& path) {
	faces_[CubemapFace::kFront] = path;
}

string Cubemap::back_face_path() const {
	return faces_[CubemapFace::kBack];
}

void Cubemap::SetBackFacePath(const std::string& path) {
	faces_[CubemapFace::kBack] = path;
}

string Cubemap::up_face_path() const {
	return faces_[CubemapFace::kUp];
}

void Cubemap::SetUpFacePath(const std::string& path) {
	faces_[CubemapFace::kUp] = path;
}

string Cubemap::down_face_path() const {
	return faces_[CubemapFace::kDown];
}

void Cubemap::SetDownFacePath(const std::string& path) {
	faces_[CubemapFace::kDown] = path;
}

string Cubemap::left_face_path() const {
	return faces_[CubemapFace::kLeft];
}

void Cubemap::SetLeftFacePath(const std::string& path) {
	faces_[CubemapFace::kLeft] = path;
}

string Cubemap::right_face_path() const {
	return faces_[CubemapFace::kRight];
}

void Cubemap::SetRightFacePath(const std::string& path) {
	faces_[CubemapFace::kRight] = path;
}

CubemapPtr Cubemap::CreateDefault() {
	return make_shared<Cubemap>(Files::DefaultCubemapFront,
								Files::DefaultCubemapBack,
								Files::DefaultCubemapUp,
								Files::DefaultCubemapDown,
								Files::DefaultCubemapLeft,
								Files::DefaultCubemapRight);
}
