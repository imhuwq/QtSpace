#ifndef QTSPACE_RESOURCE_H
#define QTSPACE_RESOURCE_H

#include <string>
#include "Common/TypeDef.h"

class Resource {
public:
    Resource();

    Resource(const Resource& rhs);

    Resource&operator=(const Resource& rhs);

	std::string uuid() const;

private:
	std::string uuid_;
};

#endif //QTSPACE_RESOURCE_H
