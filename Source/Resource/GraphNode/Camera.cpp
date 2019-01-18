#include "Camera.h"

Camera::Camera(const string &name) : Node(name, NodeType::kCamera),
                                     fov_(12.0f) {
    Translate(0, 0, 25);
    move_speed_ = 2.0f;
}

float Camera::fov() { return fov_; }

void Camera::Translate(float x, float y, float z) { Node::Translate(-x, -y, -z); }

QVector3D Camera::direction() const {
    QVector3D dir = QVector3D(0, 0, 0) - translation_;
    dir.normalize();
    return dir;
}

QVector3D Camera::right() const {
    QVector3D dir = QVector3D(0, 0, 0) - translation_;
    QVector3D rt = QVector3D::crossProduct(QVector3D(0, 1, 0), dir);
    rt.normalize();
    return rt;
}

QVector3D Camera::up() const {
    QVector3D dir = QVector3D(0, 0, 0) - translation_;
    QVector3D rt = QVector3D::crossProduct(QVector3D(0, 1, 0), dir);
    QVector3D u = QVector3D::crossProduct(dir, rt);
    u.normalize();
    return u;
}

void Camera::LookAt(float x, float y, float z) {
    transformation_.setToIdentity();
    transformation_.lookAt(translation_, QVector3D(x, y, z), up());
    dirty_ = false;
}

void Camera::Rotate(float x, float y, float z) {}

void Camera::Scale(float x, float y, float z) {}
