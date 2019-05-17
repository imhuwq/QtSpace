#include <QtMath>

#include "Camera.h"
#include "Common/Consts.h"

using namespace std;

Camera::Camera(const string &name, const QVector3D &target) : Node(name, NodeType::kCamera),
                                                              target_(target),
                                                              fov_(25.0f) {
    Translate(0, 0, 25);
    move_speed_ = 2.0f;

    direction_ = translation_ - target_;
    up_ = translation_ + Vector3D::Up;
    right_ = QVector3D::crossProduct(up_, direction_);
    right_.normalize();
}

float Camera::fov() const { return fov_; }

QVector3D Camera::target() const { return target_; }

void Camera::ComputeTransformation() {
    transformation_.setToIdentity();
    transformation_.lookAt(translation_, target_, up_);
    dirty_ = false;
}

void Camera::Zoom(float fov_delta) {
    float new_fov = fov_ + fov_delta;
    new_fov = std::max(new_fov, 10.0f);
    new_fov = std::min(new_fov, 60.0f);
    fov_ = new_fov;
}

void Camera::Orbit(float around_y_angle, float around_x_angle) {
    static QMatrix4x4 y_axis_rotation_matrix, x_axis_rotation_matrix;

    y_axis_rotation_matrix.setToIdentity();
    x_axis_rotation_matrix.setToIdentity();

    direction_ = translation_ - target_;
    y_axis_rotation_matrix.rotate(around_y_angle, up_);
    translation_ = target_ + y_axis_rotation_matrix * direction_;

    direction_ = translation_ - target_;
    right_ = QVector3D::crossProduct(up_, direction_);
    right_.normalize();

    x_axis_rotation_matrix.rotate(around_x_angle, right_);
    translation_ = target_ + x_axis_rotation_matrix * direction_;
    up_ = QVector3D::crossProduct(direction_, right_);
    up_.normalize();

    dirty_ = true;
}

void Camera::Rotate(float x, float y, float z) {}

void Camera::Scale(float x, float y, float z) {}
