#ifndef QTSPACE_RESOURCE_H
#define QTSPACE_RESOURCE_H

#include <string>

#include <QUuid>

using namespace std;

class Resource {
public:
    Resource() {
        uuid_ = QUuid::createUuid().toString().toStdString();
    }

    string uuid() const { return uuid_; }

private:
    string uuid_;
};

#endif //QTSPACE_RESOURCE_H
