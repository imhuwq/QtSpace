#include "Cubemap.h"
#include "Texture.h"
#include "Common/Files.h"

using namespace std;

Cubemap::Cubemap(const std::string &front_face,
                 const std::string &back_face,
                 const std::string &up_face,
                 const std::string &down_face,
                 const std::string &left_face,
                 const std::string &right_face) :
        front_(new Texture("front", front_face)),
        back_(new Texture("back", back_face)),
        left_(new Texture("left", left_face)),
        right_(new Texture("right", right_face)),
        up_(new Texture("up", up_face)),
        down_(new Texture("down", down_face)) {}

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
    return make_shared<Cubemap>(Files::CubemapFront,
                                Files::CubemapBack,
                                Files::CubemapUp,
                                Files::CubemapDown,
                                Files::CubemapLeft,
                                Files::CubemapRight);
}
