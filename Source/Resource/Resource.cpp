#include "Resource.h"

#include <QUuid>

using namespace std;

Resource::Resource() {
    uuid_ = QUuid::createUuid().toString().toStdString();
}

Resource::Resource(const Resource &rhs) { uuid_ = QUuid::createUuid().toString().toStdString(); }

Resource &Resource::operator=(const Resource &rhs) { 
	uuid_ = QUuid::createUuid().toString().toStdString(); 
	return *this;
}

string Resource::uuid() const { return uuid_; }
