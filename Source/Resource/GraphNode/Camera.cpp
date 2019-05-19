#include <QtMath>

#include "Camera.h"
#include "Common/Consts.h"

using namespace std;

Camera::Camera(const string &name, const QVector3D &target) :
        Node(name, NodeType::kCamera),
        target_(target),
        target_distance_(25.0f),
        fov_(25.0f) {
    Translate(0, 0, target_distance_);
    init_direction_ = translation_ - target_;
    move_speed_ = 2.0f;
}

float Camera::fov() const { return fov_; }

QVector3D Camera::target() const { return target_; }

float Camera::target_distance() const { return target_distance_; }

void Camera::ComputeTransformation() {
    if (!dirty_) return;

    transformation_.setToIdentity();
    transformation_.lookAt(translation_, target_, Vector3D::Up);
    dirty_ = false;
}

void Camera::Zoom(float fov_delta) {
    float new_fov = fov_ + fov_delta;
    new_fov = std::max(new_fov, 10.0f);
    new_fov = std::min(new_fov, 60.0f);
    fov_ = new_fov;
}


void Camera::ReSet() {
    angel_ = QVector3D(0, 0, 0);
    translation_ = target_ + init_direction_;
    dirty_ = true;
}

inline float Clamp(float val, float min_val, float max_val) {
    if (val < min_val) return min_val;
    if (val > max_val) return max_val;
    return val;
}

void Camera::Orbit(float pitch, float yaw, float roll) {
    angel_ += QVector3D(pitch, yaw, roll);
    angel_.setX(Clamp(angel_.x(), min_pitch_, max_pitch_));
    qDebug() << angel_ << endl;

    quaternion_ = QQuaternion::fromEulerAngles(angel_);
    translation_ = target_ + quaternion_.rotatedVector(init_direction_);
    dirty_ = true;
}

void Camera::Rotate(float x, float y, float z) {}

void Camera::Scale(float x, float y, float z) {}
