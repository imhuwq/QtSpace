#include "SkyBox.h"

using namespace std;

SkyBox::SkyBox() : box_(nullptr), cubemap_(nullptr) {}

kNodePtr SkyBox::box() const {
    return box_;
}

NodePtr SkyBox::box() {
    return box_;
}

void SkyBox::SetBox(NodePtr node) {
    box_ = node;
}

kCubemapPtr SkyBox::cubemap() const {
    return cubemap_;
}

CubemapPtr SkyBox::cubemap() {
    return cubemap_;
}

void SkyBox::SetCubemap(CubemapPtr cubemap) {
    cubemap_ = cubemap;
}