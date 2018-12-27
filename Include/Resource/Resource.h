#ifndef QTSPACE_RESOURCE_H
#define QTSPACE_RESOURCE_H

#include <string>

using namespace std;

class Resource {
public:
    Resource();

    string uuid() const;

private:
    string uuid_;
};

#endif //QTSPACE_RESOURCE_H
