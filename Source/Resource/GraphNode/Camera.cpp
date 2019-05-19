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
    transformation_.lookAt(translation_, target_, Vector3D::Up);
    dirty_ = false;
}

void Camera::Zoom(float fov_delta) {
    float new_fov = fov_ + fov_delta;
    new_fov = std::max(new_fov, 10.0f);
    new_fov = std::min(new_fov, 60.0f);
    fov_ = new_fov;
}

void Camera::Orbit(float orbiting_y_delta, float orbiting_x_delta) {
    static float orbiting_x_total = 0;
    static float orbiting_x_max = 85.0f;
    static float orbiting_x_min = -85.0f;
    static QMatrix4x4 orbiting_y_matrix;
    static QMatrix4x4 orbiting_x_matrix;

    orbiting_y_matrix.setToIdentity();
    orbiting_x_matrix.setToIdentity();

    orbiting_x_total += orbiting_x_delta;
    if (orbiting_x_total >= orbiting_x_max) {
        orbiting_x_delta = orbiting_x_max - (orbiting_x_total - orbiting_x_delta);
        orbiting_x_total = orbiting_x_max;
    } else if (orbiting_x_total <= orbiting_x_min) {
        orbiting_x_delta = orbiting_x_min - (orbiting_x_total - orbiting_x_delta);
        orbiting_x_total = orbiting_x_min;
    }

    direction_ = translation_ - target_;

    orbiting_y_matrix.rotate(orbiting_y_delta, Vector3D::Up);
    orbiting_x_matrix.rotate(orbiting_x_delta, right_);
    direction_ = orbiting_x_matrix * orbiting_y_matrix * direction_;
    QVector3D possible_translation = target_ + direction_;

    translation_ = possible_translation;
    right_ = QVector3D::crossProduct(Vector3D::Up, direction_);
    right_.normalize();

    dirty_ = true;
}

void Camera::Rotate(float x, float y, float z) {}

void Camera::Scale(float x, float y, float z) {}
