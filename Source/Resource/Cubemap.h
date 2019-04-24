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

	std::string front_face_path() const;

	void SetFrontFacePath(const std::string& path);

	std::string back_face_path() const;

	void SetBackFacePath(const std::string& path);

	std::string up_face_path() const;

	void SetUpFacePath(const std::string& path);

	std::string down_face_path() const;

	void SetDownFacePath(const std::string& path);

	std::string left_face_path() const;

	void SetLeftFacePath(const std::string& path);

	std::string right_face_path() const;

	void SetRightFacePath(const std::string& path);

	static CubemapPtr CreateDefault();

private:
	std::vector<std::string> faces_;
};

#endif //QTSPACE_CUBEMAP_H
