#include "Resource.h"

#include <QUuid>

Resource::Resource() {
    uuid_ = QUuid::createUuid().toString().toStdString();
}

Resource::Resource(const Resource &rhs) { uuid_ = QUuid::createUuid().toString().toStdString(); }

Resource &Resource::operator=(const Resource &rhs) { uuid_ = QUuid::createUuid().toString().toStdString(); }

string Resource::uuid() const { return uuid_; }
