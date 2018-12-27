#include "Resource/Resource.h"

#include <QUuid>

Resource::Resource() {
    uuid_ = QUuid::createUuid().toString().toStdString();
}

string Resource::uuid() const { return uuid_; }